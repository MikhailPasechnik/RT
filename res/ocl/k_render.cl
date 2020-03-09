#include "rt.hcl"

void pv(double3 v)
{
    printf("------{%f %f %f}------\n", v.x, v.y, v.z);
}

t_int pack_color(t_color *c)
{
	uchar3 t;

	t.x = c->x * 255;
	t.y = c->y * 255;
	t.z = c->z * 255;
	return ((((t.x << 8u) + t.y) << 8u) + t.z);
}

t_ray   camera_ray(t_cam *cam, float x, float y)
{
    t_ray r;
    t_mat4 m;

    r.dir = VEC(x, y, 1);
    m4_identity(&m);
    m4_set_rotation(&m, &cam->dir);
    m4_set_translate(&m, &cam->pos);
    r.orig = cam->pos;
    r.dir = normalize(m4_mul_vec3(&m, &r.dir));
    return (r);
}

__kernel void k_render(
    t_options options,
	t_cam camera,
	__global t_obj* objects,
	__global t_light* lights,
	__global t_int* output
)
{
    int id = get_global_id(0);
    int px = id % options.width;
    int py = id / options.height;
    float width = options.width;
    float height = options.height;
    float iar = width / height;

    float s = tan(deg2rad(camera.fov * 0.5));
    float x = (2 * (px + 0.5) / width - 1) * iar * s;
    float y = (1 - 2 * (py + 0.5) / height) * s;

    t_ray r = camera_ray(&camera, x, y);
//    if (id == 0)
//    {
//        print_render_args(&options, &camera, scene, lights);
//    }

    t_hit *h;
    t_hit h_;
    t_color color;
    h = intersect(objects, options.obj_count, &r, &h_);
    if (h)
		color = h->obj->mat.diffuse * dot(r.dir, h->norm * -1);
    else
		color = options.background_color;
	output[id] = pack_color(&color);
}
