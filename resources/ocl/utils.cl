#include "rt.hcl"

t_real deg2rad(t_real deg)
{
    return deg * (M_PI / 180);
}

void print_render_args(t_options *options, t_cam* camera,
        __global t_obj* scene, __global t_light* lights)
{
    printf("Options:\n"
        "\twidth: %d\n"
        "\theight: %d\n"
        "\tobj_count: %d\n"
        "\tlight_count: %d\n",
        options->width,
        options->height,
        options->obj_count,
        options->light_count
    );
    printf("Camera:\n"
        "\tfov: %f\n"
        "\tpos: %f %f %f\n",
        camera->fov,
		camera->mtx.sC,
		camera->mtx.sD,
		camera->mtx.sE
    );
    t_uint i = options->obj_count;
    while (i < options->obj_count)
    {
        printf("Obj: id: %d radius: %f pos: {%f %f %f}\n",
            scene[i].id, scene[i].radius,
            scene[i].pos.x,
            scene[i].pos.y,
            scene[i].pos.z
        );
        i++;
    }
}

uint pack_color(t_color *c)
{
	uchar3 t;

	t.x = clamp(c->x, 0.0f, 1.0f) * 255;
	t.y = clamp(c->y, 0.0f, 1.0f) * 255;
	t.z = clamp(c->z, 0.0f, 1.0f) * 255;
	return ((((t.x << 8u) + t.y) << 8u) + t.z);
}

t_vec3 dir_from_rot(t_vec3 rot)
{
	t_vec3 dir;

	dir.x = sin(radians(rot.z));
	dir.y = -(sin(radians(rot.x)) * cos(radians(rot.z)));
	dir.z = cos(radians(rot.x)) * cos(radians(rot.y));
	return (dir);
}

t_vec3 reflect(t_vec3 vec, t_vec3 normal)
{
	return (2 * dot(vec, normal) * normal - vec);
}

t_color get_direct(t_options options, t_hit hit, t_ray ray, __global t_obj *objects, __global t_light *lights,
				   __global uchar* tx_b, __global t_tx_info* txi_b)
{
	int		i;
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	t_vec3	light_dir;
	t_color	result;

	i = 0;
	result = COLOR(0,0,0,0);
	while (i < options.light_count)
	{
		if (lights[i].id == ID_DIRECT || lights[i].id == ID_POINT)
		{
			light_dir = (lights[i].id == ID_DIRECT) ? dir_from_rot(lights[i].rot) : normalize(hit.p - lights[i].pos);
			shadow_ray.o = hit.p + hit.n * 0.001f;
			shadow_ray.d = -light_dir;
			if (intersect(objects, options.obj_count, &shadow_ray, &shadow_hit, tx_b, txi_b) == -1)
				result += lights[i].intensity * lights[i].color * clamp(dot(hit.n, shadow_ray.d), 0.0f, 1.0f);
		}
		else if (lights[i].id == ID_AMB)
			result += hit.diff * lights[i].intensity  * lights[i].color;
		i++;
	}
	return (result);
}

float	get_random(unsigned int *seed0, unsigned int *seed1)
{
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);

	/* use union struct to convert int to float */
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;
	return (res.f - 2.0f) / 2.0f;
}
