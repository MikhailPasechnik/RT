#include "rt.hcl"

t_real deg2rad(t_real deg)
{
    return deg / 2 * (M_PI / 180);
}

void print_render_args(t_options *options, t_cam* camera,
        __global t_obj* scene, __global t_light* lights)
{
    printf("Options:\n"
        "\tfov: %f\n"
        "\twidth: %d\n"
        "\theight: %d\n"
        "\tobj_count: %d\n"
        "\tlight_count: %d\n",
        camera->fov,
        options->width,
        options->height,
        options->obj_count,
        options->light_count
    );
    int i = 0;
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
