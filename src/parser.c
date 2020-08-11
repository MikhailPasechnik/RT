/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:36:37 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/11 18:24:48 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define PHELP(str, p, f, app) ((t_phelp){str, ft_strlen(str), p, f, app})

static void	init_obj(t_phelp *phelp, t_obj *ol, t_app *app)
{
	ft_bzero(phelp, sizeof(t_phelp) * RT_P_OBJ_FILED_NUM);
	ft_bzero(ol, sizeof(t_obj));
	ol->mat.diff_tex_id = -1;
	ol->mat.spec_tex_id = -1;
	ol->mat.refl_tex_id = -1;
	phelp[0] = PHELP("  position:", &ol->pos, parse_vec3, app);
	phelp[1] = PHELP("  color:", &ol->mat.diff, parse_color, app);
	phelp[2] = PHELP("  rotation:", &ol->rot, parse_vec3, app);
	phelp[3] = PHELP("  radius:", &ol->radius, parse_real, app);
	phelp[4] = PHELP("  specular:", &ol->mat.specular, parse_real, app);
	phelp[5] = PHELP("  reflective:", &ol->mat.reflection, parse_real, app);
	phelp[6] = PHELP("  height:", &ol->height, parse_real, app);
	phelp[7] = PHELP("  infinite:", &ol->infinite, parse_real, app);
	phelp[8] = PHELP("  emittance:", &ol->mat.emittance, parse_vec3, app);
	phelp[9] = PHELP("  diff_texture:", &ol->mat.diff_tex_id, parse_texture,
		app);
	phelp[10] = PHELP("  spec_texture:", &ol->mat.spec_tex_id, parse_texture,
		app);
	phelp[11] = PHELP("  refl_texture:", &ol->mat.refl_tex_id, parse_texture,
		app);
}

static void	phelp_run(int size, t_phelp *phelp, char *scn)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (!ft_strncmp(scn, phelp[i].str, phelp[i].len))
		{
			phelp[i].f(scn + phelp[i].len, phelp[i].p, phelp[i].app);
			break ;
		}
		else
			i++;
	}
}

void		parser_obj(char **scn, t_app *app, int n)
{
	t_obj	ol;
	t_phelp	phelp[RT_P_OBJ_FILED_NUM];

	while (scn[n] && key_type(scn[n]))
	{
		init_obj(phelp, &ol, app);
		is_valid_obj_name(&ol, scn[n] + 8);
		n++;
		while (scn[n] && scn[n][0] != '-')
		{
			phelp_run(RT_P_OBJ_FILED_NUM, phelp, scn[n]);
			n++;
		}
		app->op.obj_count++;
		ft_lstadd(&app->obj_list, ft_lstnew(&ol, sizeof(t_obj)));
	}
	check_obj(app);
}

void		parser_light(char **scn, t_app *app, int n)
{
	t_light	ll;
	t_phelp	phelp[5];

	ft_bzero(&phelp, sizeof(t_phelp) * 5);
	phelp[0] = PHELP("  position:", &ll.pos, parse_vec3, app);
	phelp[1] = PHELP("  rotation:", &ll.rot, parse_vec3, app);
	phelp[2] = PHELP("  color:", &ll.color, parse_color, app);
	phelp[3] = PHELP("  intensity:", &ll.intensity, parse_real, app);
	phelp[4] = PHELP("  dispersion:", &ll.id, parse_id, app);
	// if (!key_type(scn[n]) || !is_valid_light_name(scn[n] + 8))
	// 	kill("Usage : - type: light");
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
	}
	check_light(app);
}
