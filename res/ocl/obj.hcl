# ifndef OBJ_HCL
# define OBJ_HCL


typedef double cl_double;
typedef double16 cl_double16;
typedef double3 cl_double3;
typedef int cl_int;
typedef uint cl_uint;


# define VEC(x, y, z)((t_vec3){x, y, z})

/*
** Include host OpenCL compatible structs
**
** Recommend declaring your structure from the widest types first
** down to the narrowest types.
** First, this avoids wasted unused spaces due to alignment.
** Second, this often avoids any headaches
** with different alignments on different devices.
*/
# include "obj.h"

typedef struct	s_hit {
	t_vec3	pos;
	t_vec3	norm;
	__global t_obj	*obj;
}				t_hit;
# endif