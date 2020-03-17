/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_attack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:42:42 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/17 12:48:25 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/obj.h"
#include "../include/rt.h"

void	ignore_str(char **ptr)
{
	while (**ptr == ' ' || **ptr == '\t' || **ptr == ':' || ft_isalpha(**ptr))
		++(*ptr);
}

int		ptr_atoi_int(char **str, int fraction)
{
	int n;
	int sign;

	n = 0;
	sign = (**str == '-' && !fraction) ? -1 : 1;
	if (**str == '+' || (**str == '-' && !fraction))
		++(*str);
	if (!ft_isdigit(**str))
		kill("Error in number!");
	while (ft_isdigit(**str))
	{
		n = n * 10 + (**str - '0');
		++(*str);
	}
	if (n * sign > INT_MAX || n * sign < INT_MIN)
		kill("Digit so big!");
	return (n * sign);
}

t_real	ptr_atoi(char **str)
{
	int	w;
	int	f;
	int d;
	int p;

	w = ptr_atoi_int(str, 0);
	p = 0;
	if ((**str) == '.')
	{
		++(*str);
		while (ft_isdigit(**str))
		{
			++(*str);
			p++;
		}
		if (p > 2)
			kill("Only two digit after '.' !");
		d = (p == 1) ? 10 : 100;
		(*str) = (d == 100) ? (*str) - 2 : (*str) - 1;
		f = (w >= 0) ? ptr_atoi_int(str, 1) : -(ptr_atoi_int(str, 1));
	}
	else
		f = 0;
	return ((t_real)w + (f ? (t_real)f / d : 0));
}

t_color	array_color(char *s)
{
	int			i;
	t_color		c;

	ignore_str(&s);
	if (*s++ != '[' && s[ft_strlen(s) - 1] != ']' && s[ft_strlen(s)] != '\0')
		kill("Error in array!");
	i = 0;
	while (*s && i++ < 3)
	{
		ignore_str(&s);
		if (i == 1)
			c.r = ptr_atoi(&s) / 255.0;
		else if (i == 2)
			c.g = ptr_atoi(&s) / 255.0;
		else if (i == 3)
			c.b = ptr_atoi(&s) / 255.0;
		else
			kill("Error in array!");
		ignore_str(&s);
		if (i < 3 && *s != ',')
			kill("Error in array coordinate!");
		++s;
		ignore_str(&s);
	}
	return (c);
}

t_vec3	array_attack(char *s)
{
	int		c;
	t_vec3	v;

	ignore_str(&s);
	if (*s++ != '[' && s[ft_strlen(s) - 1] != ']' && s[ft_strlen(s)] != '\0')
		kill("Error in array!");
	c = 0;
	while (*s && c++ < 3)
	{
		ignore_str(&s);
		if (c == 1)
			v.x = ptr_atoi(&s);
		else if (c == 2)
			v.y = ptr_atoi(&s);
		else if (c == 3)
			v.z = ptr_atoi(&s);
		else
			kill("Error in array!");
		ignore_str(&s);
		if (c < 3 && *s != ',')
			kill("Error in array coordinate!");
		++s;
		ignore_str(&s);
	}
	return (v);
}
