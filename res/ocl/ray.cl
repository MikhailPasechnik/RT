#include "rt.hcl"

t_ray   new_camera_ray(t_options *op, t_cam *cam, uint2 pixel)
{
	t_ray ray;
	t_real width;
	t_real height;
	t_real scale;
	t_vec3 dir;

	width  = op->width;
	height = op->height;
	scale  = tan(radians(cam->fov * 0.5));
	dir.x = (2 * (pixel.x + 0.5) / width - 1) * (width / height) * scale;
	dir.y = (1 - 2 * (pixel.y + 0.5) / height) * scale;
	dir.z = -1;
	ray.o = VEC(cam->mtx.sC, cam->mtx.sD, cam->mtx.sE);
	ray.d = normalize(cam_view_vec3(&cam->mtx, &dir));
	return (ray);
}
