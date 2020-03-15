#include "rt.hcl"

t_mat4 m4_mul(t_mat4 *m, t_mat4 *n)
{
    t_mat4 result = (t_mat4){
    m->s0 * n->s0 + m->s1 * n->s4 + m->s2 * n->s8 + m->s3 * n->sC,
    m->s0 * n->s1 + m->s1 * n->s5 + m->s2 * n->s9 + m->s3 * n->sD,
    m->s0 * n->s2 + m->s1 * n->s6 + m->s2 * n->sA + m->s3 * n->sE,
    m->s0 * n->s3 + m->s1 * n->s7 + m->s2 * n->sB + m->s3 * n->sF,
    m->s4 * n->s0 + m->s5 * n->s4 + m->s6 * n->s8 + m->s7 * n->sC,
    m->s4 * n->s1 + m->s5 * n->s5 + m->s6 * n->s9 + m->s7 * n->sD,
    m->s4 * n->s2 + m->s5 * n->s6 + m->s6 * n->sA + m->s7 * n->sE,
    m->s4 * n->s3 + m->s5 * n->s7 + m->s6 * n->sB + m->s7 * n->sF,
    m->s8 * n->s0 + m->s9 * n->s4 + m->sA * n->s8 + m->sB * n->sC,
    m->s8 * n->s1 + m->s9 * n->s5 + m->sA * n->s9 + m->sB * n->sD,
    m->s8 * n->s2 + m->s9 * n->s6 + m->sA * n->sA + m->sB * n->sE,
    m->s8 * n->s3 + m->s9 * n->s7 + m->sA * n->sB + m->sB * n->sF,
    m->sC * n->s0 + m->sD * n->s4 + m->sE * n->s8 + m->sF * n->sC,
    m->sC * n->s1 + m->sD * n->s5 + m->sE * n->s9 + m->sF * n->sD,
    m->sC * n->s2 + m->sD * n->s6 + m->sE * n->sA + m->sF * n->sE,
    m->sC * n->s3 + m->sD * n->s7 + m->sE * n->sB + m->sF * n->sF};
    return (result);
}

t_vec3 m4_mul_vec3(t_mat4 *m, t_vec3 *v)
{
    t_real	w;
    t_vec3	out;

    w = v->x * m->s3 + v->y * m->s7 +
        v->z * m->sB + m->sF;
    out.x = (
         v->x * m->s0 +
         v->y * m->s4 +
         v->z * m->s8 + m->sC) / w;
    out.y = (
         v->x * m->s1 +
         v->y * m->s5 +
         v->z * m->s9 + m->sD) / w;
    out.z = (
         v->x * m->s2 +
         v->y * m->s6 +
         v->z * m->sA + m->sE) / w;
    return (out);
}

t_vec3 cam_view_vec3(t_mat4 *m, t_vec3 *v)
{
	t_real	w;
	t_vec3	out;

	w = v->x * m->s3 + v->y * m->s7 +
		v->z * m->sB + m->sF;
	out.x = (
					v->x * m->s0 +
					v->y * m->s4 +
					v->z * m->s8) / w;
	out.y = (
					v->x * m->s1 +
					v->y * m->s5 +
					v->z * m->s9) / w;
	out.z = (
					v->x * m->s2 +
					v->y * m->s6 +
					v->z * m->sA) / w;
	return (out);
}

void    m4_identity(t_mat4 *m)
{
    *m = (t_mat4)(0);
    m->s0 = 1;
    m->s5 = 1;
    m->sA = 1;
    m->sF = 1;
}
/* M.s0, M.s1, M.s2, M.s3
** M.s4, M.s5, M.s6, M.s7
** M.s8, M.s9, M.sA, M.sB
** M.sC, M.sD, M.sE, M.sF
*/
void	m4_set_translate(t_mat4 *m, t_vec3 t)
{
    m->sC = t.x;
    m->sD = t.y;
    m->sE = t.z;
}

void	m4_set_rotation(t_mat4 *m, t_vec3 r)
{
    t_real	cos_v[3];
    t_real	sin_v[3];

    cos_v[2] = cos(deg2rad(r.z));
    cos_v[1] = cos(deg2rad(r.y));
    cos_v[0] = cos(deg2rad(r.x));
    sin_v[2] = sin(deg2rad(r.z));
    sin_v[1] = sin(deg2rad(r.y));
    sin_v[0] = sin(deg2rad(r.x));
    m->s0 = cos_v[2] * cos_v[1];
    m->s1 = sin_v[2] * cos_v[1];
    m->s2 = -sin_v[1];
    m->s4 = -sin_v[2] * cos_v[0] + cos_v[2] * sin_v[1] * sin_v[0];
    m->s5 = cos_v[2] * cos_v[0] + sin_v[2] * sin_v[1] * sin_v[0];
    m->s6 = cos_v[1] * sin_v[0];
    m->s8 = -sin_v[2] * -sin_v[0] + cos_v[2] * sin_v[1] * cos_v[0];
    m->s9 = cos_v[2] * -sin_v[0] + sin_v[2] * sin_v[1] * cos_v[0];
    m->sA = cos_v[1] * cos_v[0];
}
/* M.s0, M.s1, M.s2, M.s3
** M.s4, M.s5, M.s6, M.s7
** M.s8, M.s9, M.sA, M.sB
** M.sC, M.sD, M.sE, M.sF
*/
static void		coefficient(t_mat4 *m, t_real *out)
{
	out[0] = m->s6 * m->sB - m->s7 * m->sA;
	out[1] = m->s6 * m->sF - m->s7 * m->sE;
	out[3] = m->sA * m->sF - m->sB * m->sE;
	out[4] = m->s9 * m->sF - m->sB * m->sD;
	out[5] = m->s5 * m->sF - m->s7 * m->sD;
	out[6] = m->s5 * m->sB - m->s7 * m->s9;
	out[7] = m->s9 * m->sE - m->sA * m->sD;
	out[8] = m->s5 * m->sE - m->s6 * m->sD;
	out[9] = m->s5 * m->sA - m->s6 * m->s9;
	out[10] = m->s8 * m->sF - m->sB * m->sC;
	out[11] = m->s8 * m->sE - m->sA * m->sC;
	out[12] = m->s8 * m->sD - m->s9 * m->sC;
	out[13] = m->s4 * m->sF - m->s7 * m->sC;
	out[14] = m->s4 * m->sE - m->s6 * m->sC;
	out[15] = m->s4 * m->sB - m->s7 * m->s8;
	out[16] = m->s4 * m->sA - m->s6 * m->s8;
	out[17] = m->s4 * m->sD - m->s5 * m->sC;
	out[18] = m->s4 * m->s9 - m->s5 * m->s8;
}

static void		inv_apply(const t_mat4 *m,
							 const t_real *c, t_mat4 *o, t_real d)
{
	o->s0 = d * (m->s5 * c[3] - m->s6 * c[4] + m->s7 * c[7]);
	o->s1 = d * -(m->s1 * c[3] - m->s2 * c[4] + m->s3 * c[7]);
	o->s2 = d * (m->s1 * c[1] - m->s2 * c[5] + m->s3 * c[8]);
	o->s3 = d * -(m->s1 * c[0] - m->s2 * c[6] + m->s3 * c[9]);
	o->s4 = d * -(m->s4 * c[3] - m->s6 * c[10] + m->s7 * c[11]);
	o->s5 = d * (m->s0 * c[3] - m->s2 * c[10] + m->s3 * c[11]);
	o->s6 = d * -(m->s0 * c[1] - m->s2 * c[13] + m->s3 * c[14]);
	o->s7 = d * (m->s0 * c[0] - m->s2 * c[15] + m->s3 * c[16]);
	o->s8 = d * (m->s4 * c[4] - m->s5 * c[10] + m->s7 * c[12]);
	o->s9 = d * -(m->s0 * c[4] - m->s1 * c[10] + m->s3 * c[12]);
	o->sA = d * (m->s0 * c[5] - m->s1 * c[13] + m->s3 * c[17]);
	o->sB = d * -(m->s0 * c[6] - m->s1 * c[15] + m->s3 * c[18]);
	o->sC = d * -(m->s4 * c[7]- m->s5 * c[11] + m->s6 * c[12]);
	o->sD = d * (m->s0 * c[7]- m->s1 * c[11] + m->s2 * c[12]);
	o->sE = d * -(m->s0 * c[8] - m->s1 * c[14] + m->s2 * c[17]);
	o->sF = d * (m->s0 * c[9] - m->s1 * c[16] + m->s2 * c[18]);
}

t_mat4			m4_inv(t_mat4 *m)
{
	t_mat4 out;
	t_real d;
	t_real c[19];
	coefficient(m, c);
	d = m->s0 * (m->s5 * c[3] - m->s6 * c[4] + m->s7 * c[7])
		- m->s1 * (m->s4 * c[3] - m->s6 * c[10] + m->s7 * c[11])
		+ m->s2 * (m->s4 * c[4] - m->s5 * c[10] + m->s7 * c[12])
		- m->s3 * (m->s4 * c[7] - m->s5 * c[11] + m->s6 * c[12]);
	d = 1 / d;
	inv_apply(m, c, &out, d);
	return (out);
}
