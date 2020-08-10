#include "rt.hcl"

t_color translate_int_to_color(__global t_int* buffer, int id)
{
	t_color col;

	col.x = (buffer[id] & 0x00FF0000) >> 16;
	col.y = (buffer[id] & 0x0000FF00) >> 8;
	col.z = (buffer[id] & 0x000000FF);
	return (col / 255.0f);
}

t_color dof(__global t_int* color_buffer, int width, int height, int id, int r)
{
	if (r <= 0)
		return translate_int_to_color(color_buffer, id);
	int i;
	int j;
	i = -r;
	int x = id % width;
	int y = id / width;
	int n = 0;
	t_color blur2 = COLOR(0, 0, 0, 0);
	while (i < r)
	{
		j = -r;
		while (j < r)
		{
			blur2 += translate_int_to_color(color_buffer, min((x + i) + (y + j) * width, width * height));
			n++;
			j++;
		}
		i++;
	}
	return blur2 / n;
}

__kernel void k_postprocess(
		t_options options,
		__global t_int* color_buffer,
		__global float3* normal_buffer,
		__global float* depth_buffer,
		__global t_int* index_buffer,
		__global t_int* output
)
{
	int id = get_global_id(0);
	t_color out;

	out = translate_int_to_color(color_buffer, id);

    int width = options.width;
    int height = options.height;

    // UP
    int in;
    if (id - width < 0)
    	in = id;
    else
		in = id - width;

    // BOTTOM
	int is;
	if (id + width > width * height - 1)
		is = id;
	else
		is = id + width;

	int ie = id;
	int iw;

	// USA
	if ((id + 1) % width != 0)
		ie = min(id + 1, width * height - 1);
	else
		ie = id;

	// CHINA
	if (id % width != 0)
		iw = id - 1;
	else
		iw = id;

	float dc = depth_buffer[id];
	float dn = depth_buffer[in];
	float ds = depth_buffer[is];
	float de = depth_buffer[ie];
	float dw = depth_buffer[iw];

	float d_vertical   = fabs(dc - ((dn + ds) / 2.0));
	float d_horizontal = fabs(dc - ((de + dw) / 2.0));
	float d_amount = (d_vertical + d_horizontal);


	float3 nc = normal_buffer[id];
	float3 nn = normal_buffer[in];
	float3 ns = normal_buffer[is];
	float3 ne = normal_buffer[ie];
	float3 nw = normal_buffer[iw];

	float n_vertical   = dot((float3){1, 1, 1}, fabs(nc - ((nn + ns) / 2.0f)));
	float n_horizontal = dot((float3){1, 1, 1}, fabs(nc - ((ne + nw) / 2.0f)));
	float n_amount = (n_vertical + n_horizontal);

	float amount = 0;
	if (fabs(dc) < 100.0f)
		amount = min(mix(d_amount, n_amount, 0.5f), 1.0f);
	else
		amount = min(n_amount, 1.0f);
	if ( amount < 0.2f)
		amount = 0;

	if (options.edge_effect && amount)
		out = mix(out, options.edge_color, (t_color){amount, amount, amount});

	if (options.fxaa && amount)
	{
		t_color blur = (translate_int_to_color(color_buffer, id) + translate_int_to_color(color_buffer, id - 1)
						+ translate_int_to_color(color_buffer, id + 1) + translate_int_to_color(color_buffer, id - options.width)
						+ translate_int_to_color(color_buffer, id + options.width) + translate_int_to_color(color_buffer, id + options.width + 1)
						+ translate_int_to_color(color_buffer, id + options.width - 1));
		blur /= 8.0f;
		out = mix(out, blur, (t_color){amount, amount, amount} / 3.0f);
	}
	if (options.dof)
		out = dof(color_buffer, width, height, id, min(20, (int)fabs(dc / options.dof_strength - options.dof_focal_point)));

	output[id] = pack_color(&out);
}
