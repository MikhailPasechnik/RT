/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
/*   Updated: 2020/07/31 21:55:07 by bmahi            ###   ########.fr       */
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
	else
		kill("Usage objects : sphere/plane/cylinder/cone/cube/paraboloid");
	return (1);
}

int		kill(char *message)
{
	ft_printf("%s\nERRNO - %d: %s\n", message, errno, strerror(errno));
	exit(EXIT_SUCCESS);
}

void	check_obj(t_app *app)
{
	t_obj_list		*objects;
	t_obj			*obj;
	t_int			prnt;

	objects = app->obj_list;
	prnt = 1;
	while (objects)
	{
		obj = objects->content;
		obj->i = prnt;
		if (obj->id == 1)
			obj->rot = VEC(0, 0, 0);
		if (obj->radius < 0 && obj->id != 2 && obj->id != 5)
			kill("The raduis is too small!");
		if (obj->mat.specular < 0 || obj->mat.reflection.reflect < 0)
			kill("The specular and reflection must be positive!");
		prnt += 1;
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
			kill("The intensity of light must be positive!");
		if (lig->id < ID_DIRECT || lig->id > ID_AMB)
			kill("The dispersion of light must be 1, 2 or 3!");
		lights = lights->next;
	}
}
