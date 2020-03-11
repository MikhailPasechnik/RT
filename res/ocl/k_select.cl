#include "rt.hcl"

t_ray   camera_ray2(t_cam *cam, float x, float y)
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

__kernel void k_select(
		t_options options,
		t_cam camera,
		__global t_obj* objects,
		__global t_light* lights,
		__global t_int* output
)
{
	int px = get_global_id(0);
	int py = get_global_id(1);
	int id = py * options.width + px;
	float width = options.width;
	float height = options.height;
	float iar = width / height;

	float s = tan(deg2rad(camera.fov * 0.5));
	float x = (2 * (px + 0.5) / width - 1) * iar * s;
	float y = (1 - 2 * (py + 0.5) / height) * s;

	t_ray r = camera_ray2(&camera, x, y);
	    if (id == 0)
	    {
	        print_render_args(&options, &camera, objects, lights);
	    }

	int h;
	t_hit h_;
	h = intersect(objects, options.obj_count, &r, &h_);
	output[id] = h != -1 ? h + '0' : '.';
}
