#include "rt.hcl"

void print_render_args(t_options *options, t_cam* camera,
        __global t_obj* scene, __global t_light* lights)
{
    printf("Options:\n"
        "\tfov: %f\n"
        "\twidth: %d\n"
        "\theight: %d\n"
        "\tscene_size: %d\n"
        "\tlights_size: %d\n"
        "\tcameras_size: %d\n",
        options->fov,
        options->width,
        options->height,
        options->scene_size,
        options->lights_size,
        options->cameras_size
    );
    int i = 0;
    while (i < options->scene_size)
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
