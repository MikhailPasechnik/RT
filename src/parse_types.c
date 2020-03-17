/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/17 12:18:12 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/obj.h"
#include "../include/rt.h"

int		key_type(char *s)
{
	return (!ft_strncmp(s, "- type: ", 8));
}

void	parse_id(char *str, void *vp)
{
	t_int	*id;

	id = vp;
	ignore_str(&str);
	*id = ptr_atoi(&str);
}

void	parse_color(char *str, void *vp)
{
	t_color	*p;

	p = vp;
	*p = array_color(str);
}

void	parse_vec3(char *str, void *vp)
{
	t_vec3	*p;

	p = vp;
	*p = array_attack(str);
}

void	parse_real(char *str, void *vp)
{
	t_real	*p;

	p = vp;
	ignore_str(&str);
	*p = ptr_atoi(&str);
}
