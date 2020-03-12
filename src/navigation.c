#include "rt.h"


void	nav_move_camera(t_cam *cam, t_vec3 *by)
{
//	t_mat4 m;
//	t_vec3 v;
//
//	v = VEC(0, 0, 0);
//	m4_identity(&m);
//	m4_set_rotation(&m, &cam->dir);
//	v3_mull_s(&VEC(m.s0, m.s1, m.s2), by->x, &v);
//	v3_mull_s(&VEC(m.s4, m.s5, m.s6), by->y, &v);
//	v3_mull_s(&VEC(m.s8, m.s9, m.sA), by->z, &v);
//	v3_add(&cam->pos, &v, &cam->pos);
	m4_translate(&cam->mtx, by);
	printf("C:T: %f %f %f\n", cam->mtx.sC, cam->mtx.sD, cam->mtx.sE);
}


void	nav_rotate_camera(t_cam *cam, t_vec3 *rot, t_vec3 *around)
{

//	v3_add(&cam->dir, rot, &cam->dir);

	t_mat4 r;
	t_vec3 new;

	m4_extract_rotation(&cam->mtx, &r);
	new = *rot;
	new.x = TO_RAD(new.x);
	new.y = TO_RAD(new.y);
	new.z = TO_RAD(new.z);
	m4_v3_mul(&r, &new, &new);
	m4_rotate_relative(&cam->mtx, around, &new);

//
//	printf("r2: %f %f %f\n", new.x, new.y, new.z);
//
//	m4_rotate_relative(&m, around, &new);
//
//	new.y = TO_DEG(asin(-m.s2));
//	if (cos(TO_RAD(new.y)))
//	{
//		new.x = TO_DEG(atan2(m.s6, m.sA));
//		new.z = TO_DEG(atan2(m.s1, m.s0));
//	}
//	else
//	{
//		new.x = TO_DEG(atan2(-m.s4, m.s5));
//		new.z = 0;
//	}
////	v3_add(&cam->dir, &new, &cam->dir);
//	printf("r3: %f %f %f\n\n", new.x, new.y, new.z);
//	cam->dir = new;
}
