#include "rt.h"

int		transfer_objects(t_app *app)
{
	t_obj	*obj_array;
	int		i;
	int		err;
	t_list	*it;

	if (!(obj_array = ft_memalloc(sizeof(t_obj) * app->op.obj_count)))
		return (app_error("Failed to allocate memory for objects buffer!", 0));
	app->ren.obj_mem ? clReleaseMemObject(app->ren.obj_mem) : 0;
	app->obj_array ? ft_memdel((void **)&app->obj_array) : 0;
	app->obj_array = obj_array;
	i = 0;
	it = app->obj_list;
	while (it && i < app->op.obj_count)
	{
		app->obj_array[i] = *(t_obj*)it->content;
		it = it->next;
		i++;
	}
	if (i != app->op.obj_count || it != NULL)
		return (app_error("Object count not equal to Object List length!", 0));
	app->ren.obj_mem = clCreateBuffer(app->ocl.context,
			CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
			app->op.obj_count * sizeof(t_obj), app->obj_array, &err);
	err |= clSetKernelArg(app->ren.render_kernel,
						  RT_K_SCENE_ARG, sizeof(cl_mem), &app->ren.obj_mem);
	return (OCL_ERROR(err, "Failed to create gpu buffer for objects!") ? 0 : 1);
}

int		transfer_light(t_app *app)
{
	t_light	*light_array;
	int		i;
	int		err;
	t_list	*it;

	if (!(light_array = ft_memalloc(sizeof(t_light) * app->op.light_count)))
		return (app_error("Failed to allocate memory for lights buffer!", 0));
	app->ren.light_mem ? clReleaseMemObject(app->ren.light_mem) : 0;
	app->light_array ? ft_memdel((void **)&app->light_array) : 0;
	app->light_array = light_array;
	i = 0;
	it = app->light_list;
	while (it && i < app->op.light_count)
	{
		app->light_array[i] = *(t_light*)it->content;
		it = it->next;
		i++;
	}
	if (i != app->op.light_count || it != NULL)
		return (app_error("Light count not equal to Light List length!", 0));
	app->ren.light_mem = clCreateBuffer(app->ocl.context,
			CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
			app->op.light_count * sizeof(t_light), app->light_array, &err);
	err |= clSetKernelArg(app->ren.render_kernel,
						  RT_K_LIGHTS_ARG, sizeof(cl_mem), &app->ren.light_mem);
	return (OCL_ERROR(err, "Failed to create gpu buffer for lights!") ? 0 : 1);
}

int		update_object(t_app *app, t_obj *obj, int index)
{
	int err;

	err = clEnqueueWriteBuffer(app->ren.queue, app->ren.obj_mem,
		CL_TRUE, index * sizeof(t_obj), sizeof(t_obj), obj, 0, NULL, NULL
	);
	return (OCL_ERROR(err, "Failed to update object!") ? 0 : 1);
}

int		update_light(t_app *app, t_light *light, int index)
{
	int err;

	err = clEnqueueWriteBuffer(app->ren.queue, app->ren.light_mem,
		CL_TRUE, index * sizeof(t_light), sizeof(t_light), light, 0, NULL, NULL
	);
	return (OCL_ERROR(err, "Failed to update light!") ? 0 : 1);
}
