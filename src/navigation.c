#include "rt.h"


void	nav_move_camera(t_cam *cam, t_vec3 *by)
{
	t_mat4 r;
	t_mat4 rr;

	m4_extract_rotation(&cam->mtx, &r);
	m4_inv(&r, &rr);
	m4_v3_mul(&rr, by, by);
	printf("=====%f %f %f=====\n", by->x, by->y, by->z );
	m4_translate(&cam->mtx, by);
}


void	nav_rotate_camera(t_cam *cam, t_vec3 *rot, t_vec3 *around)
{
	t_mat4 r;
	t_vec3 t;
	t_real mag;

	m4_extract_translation(&cam->mtx, &t);
	m4_set_rotation(&r, rot);
	m4_v3_mul(&r, &t, &t);
//	mag = v3_mag(&t);
//	v3_norm(&t, &t);
//	t.x =  t.x * cos(TO_RAD(rot->y)) - t.x * sin(TO_RAD(rot->y));
//	t.y = t.y * sin(TO_RAD(rot->y)) + t.y * cos(TO_RAD(rot->y));
////	v3_norm(&t, &t);
//	v3_mull_s(&t, mag, &t);
	printf("=====%f %f %f=====\n", t.x, t.y, t.z );
	cam->mtx = look_at(t, *around);
//	new = *rot;
//	new.x = TO_RAD(new.x);
//	new.y = TO_RAD(new.y);
//	new.z = TO_RAD(new.z);

//	m4_rotate_relative(&cam->mtx, &r, &new);
}
