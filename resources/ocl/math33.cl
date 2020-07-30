#include "rt.hcl"

t_vec3	v3_cross(t_vec3 a, t_vec3 b)
{
    t_vec3 res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

t_vec3  v3_mult_matrix(t_mat3 rot_matrix, t_vec3 v)
{
    t_vec3 res;

    res.x = rot_matrix.a.x * v.x + rot_matrix.a.y * v.y + rot_matrix.a.z * v.z;
    res.x = rot_matrix.b.x * v.x + rot_matrix.b.y * v.y + rot_matrix.b.z * v.z;
    res.x = rot_matrix.c.x * v.x + rot_matrix.c.y * v.y + rot_matrix.c.z * v.z;
    return (res);
}
