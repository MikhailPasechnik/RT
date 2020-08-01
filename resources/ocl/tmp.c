make_float3(fabs(v.x), fabs(v.y), fabs(v.z));

// __device__ : executed on the device (GPU) and callable only from the device

struct Ray { 
 float3 orig; // ray origin
 float3 dir;  // ray direction 
 __device__ Ray(float3 o_, float3 d_) : orig(o_), dir(d_) {} 
};

enum Refl_t { DIFF, SPEC, REFR };  // material types, used in radiance(), only DIFF used here

struct Sphere {

 float rad;            // radius 
 float3 pos, emi, col; // position, emission, colour 
 Refl_t refl;          // reflection type (e.g. diffuse)

__device__ float intersect_sphere(const Ray &r) const { 
          
 // ray/sphere intersection
 // returns distance t to intersection point, 0 if no hit  
 // ray equation: p(x,y,z) = ray.orig + t*ray.dir
 // general sphere equation: x^2 + y^2 + z^2 = rad^2 
 // classic quadratic equation of form ax^2 + bx + c = 0 
 // solution x = (-b +- sqrt(b*b - 4ac)) / 2a
 // solve t^2*ray.dir*ray.dir + 2*t*(orig-p)*ray.dir + (orig-p)*(orig-p) - rad*rad = 0 
 // more details in "Realistic Ray Tracing" book by P. Shirley or Scratchapixel.com

  float3 op = pos - r.orig;    // distance from ray.orig to center sphere 
  float t, epsilon = 0.0001f;  // epsilon required to prevent floating point precision artefacts
  float b = dot(op, r.dir);    // b in quadratic equation
  float disc = b*b - dot(op, op) + rad*rad;  // discriminant quadratic equation
  if (disc<0) return 0;       // if disc < 0, no real solution (we're not interested in complex roots) 
   else disc = sqrtf(disc);    // if disc >= 0, check for solutions using negative and positive discriminant
  return (t = b - disc)>epsilon ? t : ((t = b + disc)>epsilon ? t : 0); // pick closest point in front of ray origin
 }
};

// SCENE
// 9 spheres forming a Cornell box
// small enough to be in constant GPU memory
// { float radius, { float3 position }, { float3 emission }, { float3 colour }, refl_type }
__constant__ Sphere spheres[] = {
 { 1e5f, { 1e5f + 1.0f, 40.8f, 81.6f }, { 0.0f, 0.0f, 0.0f }, { 0.75f, 0.25f, 0.25f }, DIFF }, //Left 
 { 1e5f, { -1e5f + 99.0f, 40.8f, 81.6f }, { 0.0f, 0.0f, 0.0f }, { .25f, .25f, .75f }, DIFF }, //Right 
 { 1e5f, { 50.0f, 40.8f, 1e5f }, { 0.0f, 0.0f, 0.0f }, { .75f, .75f, .75f }, DIFF }, //Back 
 { 1e5f, { 50.0f, 40.8f, -1e5f + 600.0f }, { 0.0f, 0.0f, 0.0f }, { 1.00f, 1.00f, 1.00f }, DIFF }, //Frnt 
 { 1e5f, { 50.0f, 1e5f, 81.6f }, { 0.0f, 0.0f, 0.0f }, { .75f, .75f, .75f }, DIFF }, //Botm 
 { 1e5f, { 50.0f, -1e5f + 81.6f, 81.6f }, { 0.0f, 0.0f, 0.0f }, { .75f, .75f, .75f }, DIFF }, //Top 
 { 16.5f, { 27.0f, 16.5f, 47.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DIFF }, // small sphere 1
 { 16.5f, { 73.0f, 16.5f, 78.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DIFF }, // small sphere 2
 { 600.0f, { 50.0f, 681.6f - .77f, 81.6f }, { 2.0f, 1.8f, 1.6f }, { 0.0f, 0.0f, 0.0f }, DIFF }  // Light
};

__device__ inline bool intersect_scene(const Ray &r, float &t, int &id){

 float n = sizeof(spheres) / sizeof(Sphere), d, inf = t = 1e20;  // t is distance to closest intersection, initialise t to a huge number outside scene
 for (int i = int(n); i--;)  // test all scene objects for intersection
  if ((d = spheres[i].intersect_sphere(r)) && d<t){  // if newly computed intersection distance d is smaller than current closest intersection distance
    t = d;  // keep track of distance along ray to closest intersection point 
    id = i; // and closest intersected object
  }
 return t<inf; // returns true if an intersection with the scene occurred, false when no hit
}

// random number generator from https://github.com/gz/rust-raytracer

__device__ static float getrandom(unsigned int *seed0, unsigned int *seed1) {
 *seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);  // hash the seeds using bitwise AND and bitshifts
 *seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

 unsigned int ires = ((*seed0) << 16) + (*seed1);

 // Convert to float
 union {
  float f;
  unsigned int ui;
 } res;

 res.ui = (ires & 0x007fffff) | 0x40000000;  // bitwise AND, bitwise OR

 return (res.f - 2.f) / 2.f;
}




// radiance function, the meat of path tracing 
// solves the rendering equation: 
// outgoing radiance (at a point) = emitted radiance + reflected radiance
// reflected radiance is sum (integral) of incoming radiance from all directions in hemisphere above point, 
// multiplied by reflectance function of material (BRDF) and cosine incident angle 
__device__ float3 radiance(Ray &r, unsigned int *s1, unsigned int *s2)	// returns ray color
{
	float3 accucolor = make_float3(0.0f, 0.0f, 0.0f); // accumulates ray colour with each iteration through bounce loop
	float3 mask = make_float3(1.0f, 1.0f, 1.0f); 

	// ray bounce loop (no Russian Roulette used) 
	for (int bounces = 0; bounces < 4; bounces++)
	{  // iteration up to 4 bounces (replaces recursion in CPU code)

		float t;           // distance to closest intersection 
		int id = 0;        // index of closest intersected sphere 

		// test ray for intersection with scene
		if (!intersect_scene(r, t, id))
		return make_float3(0.0f, 0.0f, 0.0f); // if miss, return black

		// else, we've got a hit!
		// compute hitpoint and normal
		const Sphere &obj = spheres[id];  // hitobject
		float3 x = r.orig + r.dir*t;          // hitpoint 
		float3 n = normalize(x - obj.pos);    // normal
		float3 nl = dot(n, r.dir) < 0 ? n : n * -1; // front facing normal

		// add emission of current sphere to accumulated colour
		// (first term in rendering equation sum) 
		accucolor += mask * obj.emi;

		// all spheres in the scene are diffuse
		// diffuse material reflects light uniformly in all directions
		// generate new diffuse ray:
		// origin = hitpoint of previous ray in path
		// random direction in hemisphere above hitpoint (see "Realistic Ray Tracing", P. Shirley)

		// create 2 random numbers
		float r1 = 2 * M_PI * getrandom(s1, s2); // pick random number on unit circle (radius = 1, circumference = 2*Pi) for azimuth
		float r2 = getrandom(s1, s2);  // pick random number for elevation
		float r2s = sqrtf(r2); 

		// compute local orthonormal basis uvw at hitpoint to use for calculation random ray direction 
		// first vector = normal at hitpoint, second vector is orthogonal to first, third vector is orthogonal to first two vectors
		float3 w = nl; 
		float3 u = normalize(cross((fabs(w.x) > .1 ? make_float3(0, 1, 0) : make_float3(1, 0, 0)), w));  
		float3 v = cross(w,u);

		// compute random ray direction on hemisphere using polar coordinates
		// cosine weighted importance sampling (favours ray directions closer to normal direction)
		float3 d = normalize(u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrtf(1 - r2));

		// new ray origin is intersection point of previous ray with scene
		r.orig = x + nl*0.05f; // offset ray origin slightly to prevent self intersection
		r.dir = d;

		mask *= obj.col;    // multiply with colour of object       
		mask *= dot(d,nl);  // weigh light contribution using cosine of angle between incident light and normal
		mask *= 2;          // fudge factor
	}

	return accucolor;
}


// __global__ : executed on the device (GPU) and callable only from host (CPU) 
// this kernel runs in parallel on all the CUDA threads

__global__ void render_kernel(float3 *output)
{

	// assign a CUDA thread to every pixel (x,y) 
	// blockIdx, blockDim and threadIdx are CUDA specific keywords
	// replaces nested outer loops in CPU code looping over image rows and image columns 
	unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;   
	unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;

	unsigned int i = (height - y - 1) * width + x; // index of current pixel (calculated using thread index) 

	unsigned int s1 = x;  // seeds for random number generator
	unsigned int s2 = y;

	// generate ray directed at lower left corner of the screen
	// compute directions for all other rays by adding cx and cy increments in x and y direction
	Ray cam(make_float3(50, 52, 295.6), normalize(make_float3(0, -0.042612, -1))); // first hardcoded camera ray(origin, direction) 
	float3 cx = make_float3(width * .5135 / height, 0.0f, 0.0f); // ray direction offset in x direction
	float3 cy = normalize(cross(cx, cam.dir)) * .5135; // ray direction offset in y direction (.5135 is field of view angle)
	float3 r; // r is final pixel color       

	r = make_float3(0.0f); // reset r to zero for every pixel 

	for (int s = 0; s < samps; s++)
	{  // samples per pixel

		// compute primary ray direction
		float3 d = cam.dir + cx * ((.25 + x) / width - .5) + cy * ((.25 + y) / height - .5);

		// create primary ray, add incoming radiance to pixelcolor
		r = r + radiance(Ray(cam.orig + d * 40, normalize(d)), &s1, &s2) * (1. / samps); 
	}       // Camera rays are pushed ^^^^^ forward to start in interior 

	// write rgb value of pixel to image buffer on the GPU, clamp value to [0.0f, 1.0f] range
	output[i] = make_float3(clamp(r.x, 0.0f, 1.0f), clamp(r.y, 0.0f, 1.0f), clamp(r.z, 0.0f, 1.0f));
}

inline float clamp(float x){ return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x; } 

inline int toInt(float x){ return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }  // convert RGB float in range [0,1] to int in range [0, 255] and perform gamma correction

int main(){

 float3* output_h = new float3[width*height]; // pointer to memory for image on the host (system RAM)
 float3* output_d;    // pointer to memory for image on the device (GPU VRAM)

 // allocate memory on the CUDA device (GPU VRAM)
 cudaMalloc(&output_d, width * height * sizeof(float3));
        
 // dim3 is CUDA specific type, block and grid are required to schedule CUDA threads over streaming multiprocessors
 dim3 block(8, 8, 1);   
 dim3 grid(width / block.x, height / block.y, 1);

 printf("CUDA initialised.\nStart rendering...\n");
 
 // schedule threads on device and launch CUDA kernel from host
 render_kernel <<< grid, block >>>(output_d);  

 // copy results of computation from device back to host
 cudaMemcpy(output_h, output_d, width * height *sizeof(float3), cudaMemcpyDeviceToHost);  
 
 // free CUDA memory
 cudaFree(output_d);  

 printf("Done!\n");

 // Write image to PPM file, a very simple image file format
 FILE *f = fopen("smallptcuda.ppm", "w");          
 fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
 for (int i = 0; i < width*height; i++)  // loop over pixels, write RGB values
  fprintf(f, "%d %d %d ", toInt(output_h[i].x),
                          toInt(output_h[i].y),
                          toInt(output_h[i].z));
 
 printf("Saved image to 'smallptcuda.ppm'\n");

 delete[] output_h;
 system("PAUSE");
}



Optionally, the following 3D vector algebra functions can be inserted at the top of the file instead of #including "cutil_math.h". Instead of creating a Vector3D class (with 3 floats), CUDA's built-in float3 type is used instead as built-in types have automated memory alignment and provide higher for performance. The "__host__ __device__" keywords in front of the functions allow them to run on both the CPU and GPU.

// 3D vector algebra from cutil_math.h
/*DEVICE_BUILTIN*/
struct float3 {float x, y, z;};
typedef struct float3 float3;
// add
inline __host__ __device__ float3 operator+(float3 a, float3 b){return make_float3(a.x + b.x, a.y + b.y, a.z + b.z);}
inline __host__ __device__ void operator+=(float3 &a, float3 b){a.x += b.x; a.y += b.y; a.z += b.z;}
inline __host__ __device__ float3 operator+(float3 a, float b){return make_float3(a.x + b, a.y + b, a.z + b);}
inline __host__ __device__ float3 operator+(float b, float3 a){return make_float3(b + a.x, b + a.y, b + a.z);}
inline __host__ __device__ void operator+=(float3 &a, float b){a.x += b; a.y += b; a.z += b;}
// subtract
inline __host__ __device__ float3 operator-(float3 a, float3 b){return make_float3(a.x - b.x, a.y - b.y, a.z - b.z);}
inline __host__ __device__ void operator-=(float3 &a, float3 b){a.x -= b.x; a.y -= b.y; a.z -= b.z;}
inline __host__ __device__ float3 operator-(float3 a, float b){return make_float3(a.x - b, a.y - b, a.z - b);}
inline __host__ __device__ float3 operator-(float b, float3 a){return make_float3(b - a.x, b - a.y, b - a.z);}
inline __host__ __device__ void operator-=(float3 &a, float b){a.x -= b; a.y -= b; a.z -= b;}
// multiply
inline __host__ __device__ float3 operator*(float3 a, float3 b){return make_float3(a.x * b.x, a.y * b.y, a.z * b.z);}
inline __host__ __device__ void operator*=(float3 &a, float3 b){a.x *= b.x; a.y *= b.y; a.z *= b.z;}
inline __host__ __device__ float3 operator*(float3 a, float b){return make_float3(a.x * b, a.y * b, a.z * b);}
inline __host__ __device__ float3 operator*(float b, float3 a){return make_float3(b * a.x, b * a.y, b * a.z);}
inline __host__ __device__ void operator*=(float3 &a, float b){a.x *= b; a.y *= b; a.z *= b;}
// divide
inline __host__ __device__ float3 operator/(float3 a, float3 b){return make_float3(a.x / b.x, a.y / b.y, a.z / b.z);}
inline __host__ __device__ void operator/=(float3 &a, float3 b){a.x /= b.x; a.y /= b.y; a.z /= b.z;}
inline __host__ __device__ float3 operator/(float3 a, float b){return make_float3(a.x / b, a.y / b, a.z / b);}
inline __host__ __device__ void operator/=(float3 &a, float b){a.x /= b; a.y /= b; a.z /= b;}
inline __host__ __device__ float3 operator/(float b, float3 a){return make_float3(b / a.x, b / a.y, b / a.z);}
// min
inline __host__ __device__ float3 fminf(float3 a, float3 b){return make_float3(fminf(a.x, b.x), fminf(a.y, b.y), fminf(a.z, b.z));}
// max
inline __host__ __device__ float3 fmaxf(float3 a, float3 b){return make_float3(fmaxf(a.x, b.x), fmaxf(a.y, b.y), fmaxf(a.z, b.z));}
// lerp
inline __device__ __host__ float3 lerp(float3 a, float3 b, float t){return a + t*(b - a);}
// clamp value v between a and b
inline __device__ __host__ float clamp(float f, float a, float b){return fmaxf(a, fminf(f, b));}
inline __device__ __host__ float3 clamp(float3 v, float a, float b){return make_float3(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b));}
inline __device__ __host__ float3 clamp(float3 v, float3 a, float3 b){return make_float3(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z));}
// dot product
inline __host__ __device__ float dot(float3 a, float3 b){return a.x * b.x + a.y * b.y + a.z * b.z;}
// length
inline __host__ __device__ float length(float3 v){return sqrtf(dot(v, v));}
// normalize
inline __host__ __device__ float3 normalize(float3 v){float invLen = rsqrtf(dot(v, v));return v * invLen;}
// floor
inline __host__ __device__ float3 floorf(float3 v){return make_float3(floorf(v.x), floorf(v.y), floorf(v.z));}
// frac
inline __host__ __device__ float fracf(float v){return v - floorf(v);}
inline __host__ __device__ float3 fracf(float3 v){return make_float3(fracf(v.x), fracf(v.y), fracf(v.z));}
// fmod
inline __host__ __device__ float3 fmodf(float3 a, float3 b){return make_float3(fmodf(a.x, b.x), fmodf(a.y, b.y), fmodf(a.z, b.z));}
// absolute value
inline __host__ __device__ float3 fabs(float3 v){return make_float3(fabs(v.x), fabs(v.y), fabs(v.z));}
// reflect 
//returns reflection of incident ray I around surface normal N
// N should be normalized, reflected vector's length is equal to length of I
inline __host__ __device__ float3 reflect(float3 i, float3 n){return i - 2.0f * n * dot(n, i);}
// cross product
inline __host__ __device__ float3 cross(float3 a, float3 b){return make