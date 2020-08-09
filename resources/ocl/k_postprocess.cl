#include "rt.hcl"

t_color translate_int_to_color(__global t_int* buffer, int id)
{
	t_color col;

	col.x = (buffer[id] & 0x00FF0000) >> 16;
	col.y = (buffer[id] & 0x0000FF00) >> 8;
	col.z = (buffer[id] & 0x000000FF);
	return (col);
}

float interpolate(float a, float b, float t)
{
	float c;
	float min;
	
	min = min(b, a);
	c = fabs(b - a);
	c *= t;
	c += min;
	return (c);
}

t_color white_lines(__global t_int* normal_buffer, __global t_int* depth_buffer, __global t_int* color_buffer, t_options options, t_int id)
{
	t_color out;
	t_color dc;
	t_color dn;
	t_color ds;
	t_color de;
	t_color dw;
	float d_vertical;
	float d_horizontal;
	float d_amount;
	t_vec3 nc;
	t_vec3 nn;
	t_vec3 ns;
	t_vec3 ne;
	t_vec3 nw;
	float n_vertical;
	float n_horizontal;
	float n_amount;
	t_vec3 blur;
	float amount;

	blur = (t_vec3){0.0f, 0.0f, 0.0f};
	dc = depth_buffer[id];
	dn = depth_buffer[id - options.width];
	ds = depth_buffer[id + options.width];
	de = depth_buffer[id + 1];
	dw = depth_buffer[id - 1];

	d_vertical   = dot((t_vec3){1.0f, 1.0f, 1.0f}, fabs(dc - ((dn + ds) / 2.0f)));
    d_horizontal = dot((t_vec3){1.0f, 1.0f, 1.0f}, fabs(dc - ((de + dw) / 2.0f)));
    d_amount = 1000.0f * (d_vertical + d_horizontal);

	nc = normal_buffer[id];
	nn = normal_buffer[id - options.width];
	ns = normal_buffer[id + options.width];
	ne = normal_buffer[id + 1];
	nw = normal_buffer[id - 1];

	n_vertical   = dot((t_vec3){1.0f, 1.0f, 1.0f}, fabs(nc - ((nn + ns) / 2.0f)));
	n_horizontal = dot((t_vec3){1.0f, 1.0f, 1.0f}, fabs(nc - ((ne + nw) / 2.0f)));
	n_amount = 50.0f * (n_vertical + n_horizontal);

	blur = (color_buffer[id] + color_buffer[id - 1] + color_buffer[id + 1] + color_buffer[id - options.width] + color_buffer[id + options.width] + color_buffer[id + options.width + 1] + color_buffer[id + options.width - 1]);
	blur /= 9.0f;

	amount = interpolate(d_amount, n_amount, 0.5f);

	out.x = interpolate((float)translate_int_to_color(color_buffer, id).x, blur.x, min(amount, 0.75f));
	out.y = interpolate((float)translate_int_to_color(color_buffer, id).y, blur.y, min(amount, 0.75f));
	out.z = interpolate((float)translate_int_to_color(color_buffer, id).z, blur.z, min(amount, 0.75f));
	return (out);
}

t_color antialising(__global t_int* normal_buffer, __global t_int* depth_buffer, __global t_int* color_buffer, t_options options, t_int id)
{
	t_color normal;
	t_color depth;

	t_color out;
	t_color dc;
	t_color dn;
	t_color ds;
	t_color de;
	t_color dw;
	float d_vertical;
	float d_horizontal;
	float d_amount;
	t_vec3 nc;
	t_vec3 nn;
	t_vec3 ns;
	t_vec3 ne;
	t_vec3 nw;
	float n_vertical;
	float n_horizontal;
	float n_amount;
	t_vec3 blur;
	float amount;

	blur = (t_vec3){0.0f, 0.0f, 0.0f};
	dc = translate_int_to_color(depth_buffer, id);
	dn = translate_int_to_color(depth_buffer, id - options.width);
	ds = translate_int_to_color(depth_buffer, id + options.width);
	de = translate_int_to_color(depth_buffer, id + 1);
	dw = translate_int_to_color(depth_buffer, id - 1);

	d_vertical   = dot((t_vec3){1.0f, 1.0f, 1.0f}, fabs(dc - ((dn + ds) / 2.0f)));
    d_horizontal = dot((t_vec3){1.0f, 1.0f, 1.0f}, fabs(dc - ((de + dw) / 2.0f)));
    d_amount = 1000.0f * (d_vertical + d_horizontal);

	nc = translate_int_to_color(normal_buffer, id);
	nn = translate_int_to_color(normal_buffer, id - options.width);
	ns = translate_int_to_color(normal_buffer, id + options.width);
	ne = translate_int_to_color(normal_buffer, id + 1);
	nw = translate_int_to_color(normal_buffer, id - 1);

	n_vertical   = dot((t_vec3){1.0f, 1.0f, 1.0f}, fabs(nc - ((nn + ns) / 2.0f)));
	n_horizontal = dot((t_vec3){1.0f, 1.0f, 1.0f}, fabs(nc - ((ne + nw) / 2.0f)));
	n_amount = 50.0f * (n_vertical + n_horizontal);

	blur = (translate_int_to_color(color_buffer, id) + translate_int_to_color(color_buffer, id - 1)
		+ translate_int_to_color(color_buffer, id + 1) + translate_int_to_color(color_buffer, id - options.width)
		+ translate_int_to_color(color_buffer, id + options.width) + translate_int_to_color(color_buffer, id + options.width + 1)
		+ translate_int_to_color(color_buffer, id + options.width - 1));
	blur /= 9.0f;

	amount = interpolate(d_amount, n_amount, 0.5f);

	out.x = interpolate((float)translate_int_to_color(color_buffer, id).x, blur.x, min(amount, 0.75f));
	out.y = interpolate((float)translate_int_to_color(color_buffer, id).y, blur.y, min(amount, 0.75f));
	out.z = interpolate((float)translate_int_to_color(color_buffer, id).z, blur.z, min(amount, 0.75f));
	return (out);
}

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

	// effect 1: contrast !!!
	// out = translate_int_to_color(color_buffer, id);
	// out.y = 0;

	// effect 2
	out = antialising(normal_buffer, depth_buffer, color_buffer, options, id);

	// effect 3
	// out = white_lines(normal_buffer, depth_buffer, color_buffer, options, id);

	out = COLOR((float)out.x / 255, (float)out.y / 255, (float)out.z / 255, 0);
	output[id] = pack_color(&out);
}
