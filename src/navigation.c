#include "rt.h"


void	nav_move_camera(t_cam *cam, t_vec3 *by)
{
	m4_translate(&cam->mtx, by);
}


void	nav_rotate_camera(t_cam *cam, t_vec3 *rot, t_vec3 *around)
{
	t_mat4 r;
	t_vec3 new;

	m4_extract_rotation(&cam->mtx, &r);
	new = *rot;
	new.x = TO_RAD(new.x);
	new.y = TO_RAD(new.y);
	new.z = TO_RAD(new.z);
	m4_v3_mul(&r, &new, &new);
	m4_rotate_relative(&cam->mtx, around, &new);
}
