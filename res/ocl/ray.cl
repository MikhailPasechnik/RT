#include "rt.hcl"

t_ray   new_camera_ray(t_options *options, t_cam *cam, uint2 pixel)
{
	t_ray	ray;
	t_mat4	m;
	float	width;
	float	height;
	float	scale;

	ray = (t_ray){0};
	width = options->width;
	height = options->height;
	scale = tan(deg2rad(cam->fov * 0.5));
	ray.dir.x = (2 * (pixel.x + 0.5) / width - 1) *  width / height * scale;
	ray.dir.y = (1 - 2 * (pixel.y + 0.5) / height) * scale;
	ray.dir.z = 1;
	m4_identity(&m);
	m4_set_rotation(&m, &cam->dir);
	m4_set_translate(&m, &cam->pos);
//	ray.orig = cam->pos;
	ray.dir = normalize(m4_mul_vec3(&m, &ray.dir));
	return (ray);
}
