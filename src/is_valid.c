/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f0rsunka <f0rsunka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
/*   Updated: 2020/06/26 18:13:59 by f0rsunka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_valid_light_name(char *str)
{
	return (!ft_strcmp(str, T_LIGHT) && str[ft_strlen(str)] == '\0');
}

int		is_valid_obj_name(t_obj *ol, char *str)
{
	ft_bzero(ol, sizeof(t_obj));
	if (!ft_strcmp(str, T_SPH))
		ol->id = ID_SPH;
	else if (!ft_strcmp(str, T_PLN))
		ol->id = ID_PLN;
	else if (!ft_strcmp(str, T_CYL))
		ol->id = ID_CYL;
	else if (!ft_strcmp(str, T_CON))
		ol->id = ID_CON;
	else if (!ft_strcmp(str, T_CUB))
		ol->id = ID_CUB;
	else if (!ft_strcmp(str, T_PAR))
		ol->id = ID_PAR;
	else if (!ft_strcmp(str, T_PCL))
		ol->id = ID_PCL;
	else if (!ft_strcmp(str, T_ELL))
		ol->id = ID_ELL;
	else
		kill("!is_valid_obj_name");
	return (1);
}

int		kill(char *message)
{
	perror(message);
	exit(1);
}

void	check_obj(t_app *app)
{
	t_obj_list		*objects;
	t_obj			*obj;

	objects = app->obj_list;
	while (objects)
	{
		obj = objects->content;
		if (obj->id == 1)
			obj->rot = VEC(0, 0, 0);
		if (obj->id != 2 && obj->id != 5 && obj->radius < 0)
			kill("Raduis so small!");
		if (obj->mat.specular < 0 || obj->mat.reflection < 0)
			kill("Parametr must be positive!");
		objects = objects->next;
	}
}

void	check_light(t_app *app)
{
	t_light_list	*lights;
	t_light			*lig;

	lights = app->light_list;
	while (lights)
	{
		lig = lights->content;
		if (lig->intensity < 0)
			kill("Intensity must be positive!");
		if (lig->id < ID_DIRECT || lig->id > ID_AMB)
			kill("Dispersion must be 1, 2 or 3!");
		lights = lights->next;
	}
}
