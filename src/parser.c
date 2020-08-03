/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:36:37 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/03 15:47:02 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define PHELP(str, p, f) ((t_phelp){str, ft_strlen(str), p, f})

void		delete_linked_lists(t_app *app)
{
	t_obj	*obj;
	t_light	*light;

	while (app->light_list)
	{
		light = app->light_list->content;
		free(light);
		app->light_list = app->light_list->next;
	}
	while (app->obj_list)
	{
		obj = app->obj_list->content;
		free(obj);
		app->obj_list = app->obj_list->next;
	}
}

static void	init_obj(t_phelp *phelp, t_obj *ol)
{
	ft_bzero(phelp, sizeof(t_phelp) * 8);
	phelp[0] = PHELP("  position:", &ol->pos, parse_vec3);
	phelp[1] = PHELP("  color:", &ol->mat.diff, parse_color);
	phelp[2] = PHELP("  rotation:", &ol->rot, parse_vec3);
	phelp[3] = PHELP("  radius:", &ol->radius, parse_real);
	phelp[4] = PHELP("  specular:", &ol->mat.specular, parse_real);
	phelp[5] = PHELP("  reflective:", &ol->mat.reflection, parse_real);
	phelp[6] = PHELP("  height:", &ol->height, parse_real);
	phelp[7] = PHELP("  infinite:", &ol->infinite, parse_real);
	phelp[8] = PHELP("  emittance:", &ol->mat.emittance, parse_vec3);
}

static void	phelp_run(int size, t_phelp *phelp, char *scn)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (!ft_strncmp(scn, phelp[i].str, phelp[i].len))
		{
			phelp[i].f(scn + phelp[i].len, phelp[i].p);
			break ;
		}
		else
			i++;
	}
}

void		parser_obj(char **scn, t_app *app, int n)
{
	t_obj	ol;
	t_phelp	phelp[9];

	init_obj(phelp, &ol);
	while (scn[n] && key_type(scn[n]) && is_valid_obj_name(&ol, scn[n] + 8))
	{
		n++;
		while (scn[n] && scn[n][0] != '-')
		{
			phelp_run(9, phelp, scn[n]);
			n++;
		}
		app->op.obj_count++;
		ft_lstadd(&app->obj_list, ft_lstnew(&ol, sizeof(t_obj)));
		check_obj(app);
	}
}

void		parser_light(char **scn, t_app *app, int n)
{
	t_light	ll;
	t_phelp	phelp[5];

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
			phelp_run(5, phelp, scn[n]);
			n++;
		}
		app->op.light_count++;
		ft_lstadd(&app->light_list, ft_lstnew(&ll, sizeof(t_light)));
		check_obj(app);
	}
}
