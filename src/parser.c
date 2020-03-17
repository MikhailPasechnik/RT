/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:36:37 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/17 13:16:38 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/obj.h"
#include "../include/rt.h"

#define PHELP(str, p, f) ((t_phelp){str, ft_strlen(str), p, f})

void	parser_obj(char **scn, t_app *app, int n)
{
	t_obj	ol;
	int		i;
	t_phelp	phelp[8];
	int		phelp_len;

	phelp_len = 8;
	ft_bzero(&phelp, sizeof(t_phelp) * 8);
	phelp[0] = PHELP("  position:", &ol.pos, parse_vec3);
	phelp[1] = PHELP("  color:", &ol.mat.diffuse, parse_color);
	phelp[2] = PHELP("  rotation:", &ol.rot, parse_vec3);
	phelp[3] = PHELP("  radius:", &ol.radius, parse_real);
	phelp[4] = PHELP("  specular:", &ol.mat.specular, parse_real);
	phelp[5] = PHELP("  reflective:", &ol.mat.reflection, parse_real);
	phelp[6] = PHELP("  height:", &ol.height, parse_real);
	phelp[7] = PHELP("  infinite:", &ol.infinite, parse_real);
	while (scn[n] && key_type(scn[n]) && is_valid_obj_name(scn[n] + 8))
	{
		ft_bzero(&ol, sizeof(t_obj));
		if (!ft_strcmp(scn[n] + 8, T_SPH))
			ol.id = ID_SPH;
		else if (!ft_strcmp(scn[n] + 8, T_PLN))
			ol.id = ID_PLN;
		else if (!ft_strcmp(scn[n] + 8, T_CYL))
			ol.id = ID_CYL;
		else if (!ft_strcmp(scn[n] + 8, T_CON))
			ol.id = ID_CON;
		else if (!ft_strcmp(scn[n] + 8, T_CUB))
			ol.id = ID_CUB;
		n++;
		while (scn[n] && scn[n][0] != '-')
		{
			i = 0;
			while (i < phelp_len)
			{
				if (!ft_strncmp(scn[n], phelp[i].str, phelp[i].len))
				{
					phelp[i].f(scn[n] + phelp[i].len, phelp[i].p);
					break ;
				}
				else
					i++;
			}
			n++;
		}
		check_obj(app);
		app->op.obj_count++;
		ft_lstadd(&app->obj_list, ft_lstnew(&ol, sizeof(t_obj)));
	}
}

void	parser_light(char **scn, t_app *app, int n)
{
	t_light	ll;
	int		i;
	t_phelp	phelp[5];
	int		phelp_len;

	phelp_len = 5;
	ft_bzero(&phelp, sizeof(t_phelp) * 5);
	phelp[0] = PHELP("  position:", &ll.pos, parse_vec3);
	phelp[1] = PHELP("  rotation:", &ll.rot, parse_vec3);
	phelp[2] = PHELP("  color:", &ll.color, parse_color);
	phelp[3] = PHELP("  intensity:", &ll.intensity, parse_real);
	phelp[4] = PHELP("  dispersion:", &ll.id, parse_id);
	while (key_type(scn[n]) && is_valid_light_name(scn[n] + 8))
	{
		ft_bzero(&ll, sizeof(t_light));
		n++;
		while (scn[n][0] != '-')
		{
			i = 0;
			while (i < phelp_len)
			{
				if (!ft_strncmp(scn[n], phelp[i].str, phelp[i].len))
				{
					phelp[i].f(scn[n] + phelp[i].len, phelp[i].p);
					break ;
				}
				else
					i++;
			}
			n++;
		}
		check_obj(app);
		app->op.light_count++;
		ft_lstadd(&app->light_list, ft_lstnew(&ll, sizeof(t_light)));
	}
}
