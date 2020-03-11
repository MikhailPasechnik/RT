#include "rt.hcl"

t_real deg2rad(t_real deg)
{
    return deg / 2 * (M_PI / 180);
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
        "\tpos: %f %f %f\n"
        "\trot: %f %f %f\n",
        camera->fov,
		camera->pos.x,
		camera->pos.y,
		camera->pos.z,
		camera->rot.x,
		camera->rot.y,
		camera->rot.z
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
