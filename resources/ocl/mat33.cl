#include "rt.hcl"

float3	v3_cross(float3 a, float3 b)
{
    float3 res;

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

float	v3_dot_product(t_vec3 v1, t_vec3 v2)
{
	float dp;

	dp = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (dp);
}

t_vec3		v3_mult_vec_const(t_vec3 v, float n)
{
	return ((t_vec3){v.x * n, v.y * n, v.z * n});
}

t_color		v3_division_vec_on_const(t_color v, float n)
{
	v.x = v.x / n;
	v.y = v.y / n;
	v.z = v.z / n;
	return (v);
}