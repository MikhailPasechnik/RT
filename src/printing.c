/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:36:42 by bmahi             #+#    #+#             */
/*   Updated: 2020/06/26 22:44:26 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	printing_light(t_app *app)
{
	t_light			*light;
	t_light_list	*list;

	list = app->light_list;
	while (list)
	{
		light = list->content;
		if (light->id == ID_DIRECT)
			ft_printf("\tDirect :\t");
		else if (light->id == ID_POINT)
			ft_printf("\tPoint :\t\t");
		else if (light->id == ID_AMB)
			ft_printf("\tAmbient :\t");
		ft_printf("[%.2f, %.2f, %.2f]\n", light->pos.v4[0], light->pos.v4[1],
			light->pos.v4[2]);
		list = list->next;
	}
}

void	printing_obj_r(t_app *app)
{
	t_obj		*obj;
	t_obj_list	*list;

	list = app->obj_list;
	while (list)
	{
		obj = list->content;
		if (obj->id == ID_CON || obj->id == ID_CYL)
		{
			obj->id == ID_CON ? ft_printf("\tCone :\t\t") :
				ft_printf("\tCylinder :\t");
			ft_printf("[%.2f, %.2f, %.2f]\n\t\t\bradius : %.0f\n",
				obj->pos.v4[0], obj->pos.v4[1], obj->pos.v4[2], obj->radius);
			ft_printf("\t\t\bheight : %.0f\n", obj->height);
		}
		else if (obj->id == ID_SPH || obj->id == ID_PAR)
		{
			obj->id == ID_SPH ? ft_printf("\tSphere :\t") :
				ft_printf("\tParaboloid :\t");
			ft_printf("[%.2f, %.2f, %.2f]\n\t\t\bradius : %.0f\n",
				obj->pos.v4[0], obj->pos.v4[1], obj->pos.v4[2], obj->radius);
		}
		list = list->next;
	}
}

void	printing_obj(t_app *app)
{
	t_obj		*obj;
	t_obj_list	*list;

	list = app->obj_list;
	while (list)
	{
		obj = list->content;
		if (obj->id == ID_CUB)
			ft_printf("\tCube :\t\t[%.2f, %.2f, %.2f]\n\t\t\bheight : %.0f\n",
				obj->pos.v4[0], obj->pos.v4[1], obj->pos.v4[2], obj->height);
		else if (obj->id == ID_PLN)
			ft_printf("\tPlane :\t\t[%.2f, %.2f, %.2f]\n", obj->pos.v4[0],
			obj->pos.v4[1], obj->pos.v4[2]);
		list = list->next;
    }
}
