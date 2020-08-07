#include "rt.hcl"

t_ray   new_camera_ray(t_options *op, t_cam *cam, uint2 pixel)
{
	t_ray ray;
	t_real width;
	t_real height;
	t_real scale;
	t_vec3 dir;
	t_real k;

	width  = op->width;
	height = op->height;
	
	scale = tan(cam->fov / 5.0f) * (width / height);

	if (width == height)
	{
		k = 1.0f;
		dir.x = (2 * (pixel.x + 0.5) / width - 1) * (width / height) * scale;
		dir.y = (2 * (pixel.y + 0.5) / height - 1) * scale / k;
	}
	else if (width > height)
	{
		k = width / 1000.0f / (height / 1000.0f);
		dir.x = (2 * (pixel.x + 0.5) / width - 1) * (width / height) * scale;
		dir.y = (2 * (pixel.y + 0.5) / height - 1) * scale / k;
	}
	else if (height > width)
	{
		k = height / 1000.f / (width / 1000.0f);
		dir.x = (2 * (pixel.x + 0.5) / width - 1) * (width / height) * scale / k;
		dir.y = (2 * (pixel.y + 0.5) / height - 1) * scale;
	}
	dir.z = -1;
	ray.o = VEC(cam->mtx.sC, cam->mtx.sD, cam->mtx.sE);
	ray.d = normalize(cam_view_vec3(&cam->mtx, &dir));
	return (ray);
}
