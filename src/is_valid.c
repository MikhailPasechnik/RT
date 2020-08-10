/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/10 17:16:48 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_valid_light_name(char *str)
{
	return (!ft_strcmp(str, T_LIGHT) && str[ft_strlen(str)] == '\0');
}

int		is_valid_obj_name(t_obj *ol, char *str)
{
	if (!ft_strcmp(str, T_SPH) || !ft_strcmp(str, T_PLN))
		ol->id = !ft_strcmp(str, T_SPH) ? ID_SPH : ID_PLN;
	else if (!ft_strcmp(str, T_CYL) || !ft_strcmp(str, T_CON))
		ol->id = !ft_strcmp(str, T_CYL) ? ID_CYL : ID_CON;
	else if (!ft_strcmp(str, T_CUB) || !ft_strcmp(str, T_PAR))
		ol->id = !ft_strcmp(str, T_CUB) ? ID_CUB : ID_PAR;
	else if (!ft_strcmp(str, T_PCL) || !ft_strcmp(str, T_ELL))
		ol->id = !ft_strcmp(str, T_PCL) ? ID_PCL : ID_ELL;
	else if (!ft_strcmp(str, T_HCL) || !ft_strcmp(str, T_HTS))
		ol->id = !ft_strcmp(str, T_HCL) ? ID_HCL : ID_HTS;
	else if (!ft_strcmp(str, T_HPR))
		ol->id = ID_HPR;
	else
		kill("Usage objects :\nsphere / plane / cylinder / cone / ellipse\n\
parabolic cylinder / hyperbolic cylinder / paraboloid\n\
hyperbolic cylinder / hyperboloid with two sheets\n\
cube or hyperbolic paraboloid\n");
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

	objects = app->obj_list;
	while (objects)
	{
		obj = objects->content;
		if (obj->id == 1)
			obj->rot = VEC(0, 0, 0);
		if (obj->radius < 0 && obj->id != 2 && obj->id != 5)
			kill("The raduis is too small!");
		if (obj->mat.specular < 0 || obj->mat.reflection < 0 ||
			obj->mat.specular > 1 || obj->mat.reflection > 1)
			kill("The specular or reflection must be in the range 0..1!");
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
