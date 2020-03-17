/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/17 13:06:09 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/obj.h"
#include "../include/rt.h"

int		is_valid_light_name(char *str)
{
	return (!ft_strcmp(str, T_LIGHT) && str[ft_strlen(str)] == '\0');
}

int		is_valid_obj_name(char *str)
{
	return ((!ft_strcmp(str, T_CON) || !ft_strcmp(str, T_CUB) \
		|| !ft_strcmp(str, T_CYL) || !ft_strcmp(str, T_PLN) \
		|| !ft_strcmp(str, T_SPH)) && str[ft_strlen(str)] == '\0');
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
