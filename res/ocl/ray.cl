#include "rt.hcl"

t_ray   new_camera_ray(t_options *op, t_cam *cam, uint2 pixel)
{
	t_ray r;
	t_mat4 m;
	t_real width ;
	t_real height;
	t_real scale ;

	width  = op->width;
	height = op->height;
	scale  = tan(deg2rad(cam->fov * 0.5));
	r.dir.x = (2 * (pixel.x + 0.5) / width - 1) * (width / height) * scale;
	r.dir.y = (1 - 2 * (pixel.y + 0.5) / height) * scale;
	r.dir.z = 1;
	m4_identity(&m);
	m4_set_rotation(&m, &cam->rot);
	r.orig = cam->pos;
	r.dir = normalize(m4_mul_vec3(&m, &r.dir));
	return (r);
}
