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
	int2 pix;
	t_color out;
	t_int r, g, b;

	r = (color_buffer[id] & 0x00FF0000) >> 16;
	g = (color_buffer[id] & 0x0000FF00) >> 8;
	b = (color_buffer[id] & 0x000000FF);

	// pix.x = id % options.width;
	// pix.y = id / options.width;

	// Супер эффект!!
	g = 0;

	// effect 1 (contrast):
	out = (color_buffer[id - 1] + color_buffer[id + 1] + color_buffer[id - options.width] + color_buffer[id + options.width] + color_buffer[id + options.width + 1] + color_buffer[id + options.width - 1]);
	out = out / 8.0f;

	// int nx = 200;
	// int ny = 100;
	// int ns = 100;

	// for (int j = ny - 1; j >= 0; j--)
	// {
	// 	for (int i = 0; i < nx; i++)
	// 	{
	// 		// t_vec3 col(0,0,0);
	// 		for (int s = 0; s < ns; s++)
	// 		{
	// 			float u = float(i + drand48())/float(nx); // 0~1
	// 			float v = float(j + drand48())/float(ny);
	// 			ray r = cam.get_ray(u,v);
	// 			col += color(r);
	// 		}
	// 		col /= float(ns);

	// 		int ir = int(255.99 * col[0]);
	// 		int ig = int(255.99 * col[1]);
	// 		int ib = int(255.99 * col[2]);
	// 	}
	// }



	out = COLOR((float)r / 255, (float)g / 255, (float)b / 255, 0);
	output[id] = pack_color(&out);
}
