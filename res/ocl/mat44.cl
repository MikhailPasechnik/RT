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
/* M.s0, M.s1, M.s2, M.s3
** M.s4, M.s5, M.s6, M.s7
** M.s8, M.s9, M.sA, M.sB
** M.sC, M.sD, M.sE, M.sF
*/
t_vec3 m4_mul_vec3(t_mat4 *m, t_vec3 *v)
{
    t_real	w;
    t_vec3	out;

    w = v->x * m->s3 + v->y * m->s7 +
        v->z * m->s8 + m->sF;
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
