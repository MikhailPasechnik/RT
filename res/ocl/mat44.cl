#include "rt.hcl"

t_mat4 m4_mul(t_mat4 M, t_mat4 N)
{
    t_mat4 result = (t_mat4){
            M.s0 * N.s0 + M.s1 * N.s4 + M.s2 * N.s8 + M.s3 * N.sC,
            M.s0 * N.s1 + M.s1 * N.s5 + M.s2 * N.s9 + M.s3 * N.sD,
            M.s0 * N.s2 + M.s1 * N.s6 + M.s2 * N.sA + M.s3 * N.sE,
            M.s0 * N.s3 + M.s1 * N.s7 + M.s2 * N.sB + M.s3 * N.sF,
            M.s4 * N.s0 + M.s5 * N.s4 + M.s6 * N.s8 + M.s7 * N.sC,
            M.s4 * N.s1 + M.s5 * N.s5 + M.s6 * N.s9 + M.s7 * N.sD,
            M.s4 * N.s2 + M.s5 * N.s6 + M.s6 * N.sA + M.s7 * N.sE,
            M.s4 * N.s3 + M.s5 * N.s7 + M.s6 * N.sB + M.s7 * N.sF,
            M.s8 * N.s0 + M.s9 * N.s4 + M.sA * N.s8 + M.sB * N.sC,
            M.s8 * N.s1 + M.s9 * N.s5 + M.sA * N.s9 + M.sB * N.sD,
            M.s8 * N.s2 + M.s9 * N.s6 + M.sA * N.sA + M.sB * N.sE,
            M.s8 * N.s3 + M.s9 * N.s7 + M.sA * N.sB + M.sB * N.sF,
            M.sC * N.s0 + M.sD * N.s4 + M.sE * N.s8 + M.sF * N.sC,
            M.sC * N.s1 + M.sD * N.s5 + M.sE * N.s9 + M.sF * N.sD,
            M.sC * N.s2 + M.sD * N.s6 + M.sE * N.sA + M.sF * N.sE,
            M.sC * N.s3 + M.sD * N.s7 + M.sE * N.sB + M.sF * N.sF};
    return (result);
}
