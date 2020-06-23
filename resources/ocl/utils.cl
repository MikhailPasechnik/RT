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
    int i = options->obj_count;
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
	return (vec - 2 * dot(vec, normal) * normal);
}
