/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
/*   Updated: 2020/07/31 22:05:11 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		key_type(char *s)
{
	return (!ft_strncmp(s, "- type: ", 8));
}

void	parse_id(char *str, void *vp, t_app *app)
{
	t_int	*id;

	(void)app;
	id = vp;
	ignore_str(&str, 0);
	*id = ptr_atoi(&str);
}

void	parse_color(char *str, void *vp, t_app *app)
{
	t_color	*p;

	(void)app;
	p = vp;
	*p = array_color(str);
}

void	parse_vec3(char *str, void *vp, t_app *app)
{
	t_vec3	*p;

	(void)app;
	p = vp;
	*p = array_attack(str);
}

void	parse_real(char *str, void *vp, t_app *app)
{
	t_real	*p;

	(void)app;
	p = vp;
	ignore_str(&str, 0);
	*p = ptr_atoi(&str);
}
