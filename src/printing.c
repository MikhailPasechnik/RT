/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:36:42 by bmahi             #+#    #+#             */
/*   Updated: 2020/07/06 19:58:34 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	printing_light(t_app *app)
{
	t_light			*light;
	t_light_list	*list;

	ft_printf("\nList of lights :\n");
	list = app->light_list;
	while (list)
	{
		light = list->content;
		if (light->id == ID_DIRECT)
			ft_printf("Direct :\n");
		else if (light->id == ID_POINT)
			ft_printf("Point :\n");
		else if (light->id == ID_AMB)
			ft_printf("Ambient :\n");
		ft_printf("\tColor : [%.0f, %.0f, %.0f]\n", light->color.v4[0] * 255,
			light->color.v4[1] * 255, light->color.v4[2] * 255);
		ft_printf("\tPosition : [%.2f, %.2f, %.2f]\n", light->pos.v4[0],
			light->pos.v4[1], light->pos.v4[2]);
		ft_printf("\tRotation : [%.2f, %.2f, %.2f]\n\tIntensity : %.2f\n",
			light->rot.v4[0], light->rot.v4[1], light->rot.v4[2],
			light->intensity);
		list = list->next;
	}
}

void	print_parametrs(t_obj *obj)
{
	ft_printf("\tColor : [%.0f, %.0f, %.0f]\n", obj->mat.diff.v4[0] * 255,
		obj->mat.diff.v4[1] * 255, obj->mat.diff.v4[2] * 255);
	ft_printf("\tPosition : [%.2f, %.2f, %.2f]\n", obj->pos.v4[0],
		obj->pos.v4[1], obj->pos.v4[2]);
	ft_printf("\tRotation : [%.2f, %.2f, %.2f]\n\tReflection : %.2f\n",
		obj->rot.v4[0], obj->rot.v4[1], obj->rot.v4[2],
		obj->mat.reflection);
	ft_printf("\tSpecularity : %.2f\n", obj->mat.specular);
}

void	printing_obj(t_app *app)
{
	t_obj		*obj;
	t_obj_list	*list;

	ft_printf("\nList of objects :\n");
	list = app->obj_list;
	while (list)
	{
		obj = list->content;
		if (obj->id == ID_CUB || obj->id == ID_PLN)
			obj->id != ID_CUB ? ft_printf("Plane :\n") :
				ft_printf("Cube :\n\tHeight : %.0f\n", obj->height);
		else if (!obj->infinite && (obj->id == ID_CON || obj->id == ID_CYL))
			obj->id == ID_CON ? ft_printf("Cone :\n\tHeight : %.0f\n",
				obj->height) : ft_printf("Cylinder :\n\tHeight : %.0f\n",
				obj->height);
		else if (obj->id == ID_SPH || obj->id == ID_PAR)
			obj->id == ID_SPH ? ft_printf("Sphere :\n")
				: ft_printf("Paraboloid :\n");
		if (obj->id != ID_PLN && obj->id != ID_CUB)
			ft_printf("\tRadius : %.0f\n", obj->radius);
		print_parametrs(obj);
		list = list->next;
	}
}
