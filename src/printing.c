/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:36:42 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/05 19:15:36 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		printing_light(int fd, t_app *app)
{
	t_light	*light;
	int		с;

	с = 0;
	while (с <= app->op.light_count)
	{
		light = &((t_light*)app->ren.light_buf.host)[с];
		if (light->id == ID_DIRECT)
			ft_fprintf(fd, "Direct #%d:\n", light->i);
		else if (light->id == ID_POINT)
			ft_fprintf(fd, "Point #%d:\n", light->i);
		else if (light->id == ID_AMB)
			ft_fprintf(fd, "Ambient #%d:\n", light->i);
		ft_fprintf(fd, "\tColor : [%.0f, %.0f, %.0f]\n"
			"\tPosition : [%.2f, %.2f, %.2f]\n"
			"\tRotation : [%.2f, %.2f, %.2f]\n\tIntensity : %.2f\n",
			light->color.v4[0] * 255, light->color.v4[1] * 255,
			light->color.v4[2] * 255, light->pos.v4[0], light->pos.v4[1],
			light->pos.v4[2], light->rot.v4[0], light->rot.v4[1],
			light->rot.v4[2], light->intensity);
			с++;
	}	
}

void		print_parametrs(int fd, t_obj *obj)
{
	if (obj->id == ID_CUB || (!obj->infinite && (obj->id == ID_CON
		|| obj->id == ID_CYL)))
		ft_fprintf(fd, "\tHeight : %.2f\n", obj->height);
	if (obj->id != ID_PLN && obj->id != ID_CUB)
		ft_fprintf(fd, "\tRadius : %.2f\n", obj->radius);
	ft_fprintf(fd, "\tColor : [%.0f, %.0f, %.0f]\n"
		"\tEmittance : [%.0f, %.0f, %.0f]\n"
		"\tPosition : [%.2f, %.2f, %.2f]\n"
		"\tRotation : [%.2f, %.2f, %.2f]\n\tReflection : %.2f\n"
		"\tSpecularity : %.2f\n", obj->mat.diff.v4[0] * 255,
		obj->mat.diff.v4[1] * 255, obj->mat.diff.v4[2] * 255,
		obj->mat.emittance.v4[0], obj->mat.emittance.v4[1],
		obj->mat.emittance.v4[2], obj->pos.v4[0], obj->pos.v4[1],
		obj->pos.v4[2], obj->rot.v4[0], obj->rot.v4[1],
		obj->rot.v4[2], obj->mat.reflection, obj->mat.specular);
}

void		printing_obj(int fd, t_app *app)
{
	t_obj	*obj;
	int		с;

	с = 0;
	while (с <= app->op.obj_count)
	{
		obj = &((t_obj*)app->ren.obj_buf.host)[с];
		if (obj->id == ID_CUB || obj->id == ID_PLN)
			obj->id != ID_CUB ? ft_fprintf(fd, "Plane #%d:\n", obj->i)
			: ft_fprintf(fd, "Cube #%d:\n", obj->i);
		else if (obj->id == ID_CON || obj->id == ID_CYL)
			obj->id == ID_CON ? ft_fprintf(fd, "Cone #%d:\n", obj->i)
			: ft_fprintf(fd, "Cylinder #%d:\n", obj->i);
		else if (obj->id == ID_SPH || obj->id == ID_PAR)
			obj->id == ID_SPH ? ft_fprintf(fd, "Sphere #%d:\n", obj->i)
			: ft_fprintf(fd, "Paraboloid #%d:\n", obj->i);
		print_parametrs(fd, obj);
		с++;
	}
	close(fd);
}

int			save_scene(t_app *app, t_int chng)
{
	int		fd;
	char	name[150];

	file_name(name);
	(ft_strlen(name) + 4 < FILENAME_MAX) ? ft_sprintf(name, "%s.txt", name) : 0;
	if (!chng)
	{
		if ((fd = open(name, O_RDWR | O_CREAT, 0666)) < 0)
			return (0);
		ft_fprintf(fd, "\tScene from ./scene/*.yml :\n\n"
			"Camera :\n\tFOV : %.0f\n\tPosition : [%.2f, %.2f, %.2f]\n",
			app->cam.fov, app->cam.mtx.sC, app->cam.mtx.sD, app->cam.mtx.sE);
	}
	if (chng)
	{
		if ((fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0600)) < 0)
			return (0);
		ft_fprintf(fd, "\n\tYou saved the changes in the scene!\n");
	}
	ft_fprintf(fd, "\nList of lights :\n");
	printing_light(fd, app);
	ft_fprintf(fd, "\nList of objects :\n");
	printing_obj(fd, app);
	return (1);
}
