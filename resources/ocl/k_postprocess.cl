#include "rt.hcl"

__kernel void k_postprocess(
		t_options options,
		__global t_int* color_buffer,
		__global t_int* normal_buffer,
		__global t_int* depth_buffer,
		__global t_int* index_buffer,
		__global t_int* output
)
{
	int id = get_global_id(0);
	t_color out;
	t_int r, g, b;

	r = (color_buffer[id] & 0x00FF0000) >> 16;
	g = (color_buffer[id] & 0x0000FF00) >> 8;
	b = (color_buffer[id] & 0x000000FF);


	// Супер эффект!!
	g = 0;
	//

	out = COLOR((float)r / 255, (float)g / 255, (float)b / 255, 0);
	output[id] = pack_color(&out);
}
