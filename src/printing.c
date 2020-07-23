/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:36:42 by bmahi             #+#    #+#             */
/*   Updated: 2020/07/23 23:39:07 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	printing_light(int fd, t_app *app)
{
	t_light			*light;
	t_light_list	*list;

	ft_fprintf(fd, "\nList of lights :\n");
	list = app->light_list;
	while (list)
	{
		light = list->content;
		if (light->id == ID_DIRECT)
			ft_fprintf(fd, "Direct :\n");
		else if (light->id == ID_POINT)
			ft_fprintf(fd, "Point :\n");
		else if (light->id == ID_AMB)
			ft_fprintf(fd, "Ambient :\n");
		ft_fprintf(fd, "\tColor : [%.0f, %.0f, %.0f]\n"
			"\tPosition : [%.2f, %.2f, %.2f]\n"
			"\tRotation : [%.2f, %.2f, %.2f]\n\tIntensity : %.2f\n",
			light->color.v4[0] * 255, light->color.v4[1] * 255,
			light->color.v4[2] * 255, light->pos.v4[0], light->pos.v4[1],
			light->pos.v4[2], light->rot.v4[0], light->rot.v4[1],
			light->rot.v4[2], light->intensity);
		list = list->next;
	}
}

void	print_parametrs(int fd, t_obj *obj)
{
	ft_fprintf(fd, "\tColor : [%.0f, %.0f, %.0f]\n"
		"\tPosition : [%.2f, %.2f, %.2f]\n"
		"\tRotation : [%.2f, %.2f, %.2f]\n\tReflection : %.2f\n"
		"\tSpecularity : %.2f\n", obj->mat.diff.v4[0] * 255,
		obj->mat.diff.v4[1] * 255, obj->mat.diff.v4[2] * 255, obj->pos.v4[0],
		obj->pos.v4[1], obj->pos.v4[2], obj->rot.v4[0], obj->rot.v4[1],
		obj->rot.v4[2], obj->mat.reflection, obj->mat.specular);
}

void	printing_obj(int fd, t_app *app)
{
	t_obj		*obj;
	t_obj_list	*list;

	ft_fprintf(fd, "\nList of objects :\n");
	list = app->obj_list;
	while (list)
	{
		obj = list->content;
		if (obj->id == ID_CUB || obj->id == ID_PLN)
			obj->id != ID_CUB ? ft_fprintf(fd, "Plane :\n") :
				ft_fprintf(fd, "Cube :\n\tHeight : %.0f\n", obj->height);
		else if (!obj->infinite && (obj->id == ID_CON || obj->id == ID_CYL))
			obj->id == ID_CON ? ft_fprintf(fd, "Cone :\n\tHeight : %.0f\n",
				obj->height) : ft_fprintf(fd, "Cylinder :\n\tHeight : %.0f\n",
				obj->height);
		else if (obj->id == ID_SPH || obj->id == ID_PAR)
			obj->id == ID_SPH ? ft_fprintf(fd, "Sphere :\n")
				: ft_fprintf(fd, "Paraboloid :\n");
		if (obj->id != ID_PLN && obj->id != ID_CUB)
			ft_fprintf(fd, "\tRadius : %.0f\n", obj->radius);
		print_parametrs(fd, obj);
		list = list->next;
	}
}

int		save_prtcl(t_app *app, const char *file_name)
{
	int		fd;
	char	name[FILENAME_MAX];

	if (ft_strlen(file_name) + 4 > FILENAME_MAX)
		return (0);
	ft_sprintf(name, "%s.txt", file_name);
	if ((fd = open(name, O_RDWR | O_CREAT, 0666)) < 0)
		return (0);
	ft_fprintf(fd, "\tScene from ./scene/*.yml :\n\n"
		"Camera :\n\tFOV : %.0f\n\tPosition : [%.2f, %.2f, %.2f]\n",
		app->cam.fov, app->cam.mtx.sC, app->cam.mtx.sD, app->cam.mtx.sE);
	printing_light(fd, app);
	printing_obj(fd, app);
	write(fd, "\n", 1);
	close(fd);
	return (1);
}
