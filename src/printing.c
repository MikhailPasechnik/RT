/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:36:42 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/11 18:45:57 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		printing_light(int fd, t_app *app)
{
	t_light	*light;
	t_uint	c;

	c = 0;
	while (c < app->op.light_count)
	{
		light = &((t_light*)app->ren.light_buf.host)[c];
		ft_fprintf(fd, "- type: light\n  position:     [%.2f, %.2f, %.2f]\n"
			"  rotation:     [%.2f, %.2f, %.2f]\n"
			"  color:        [%.0f, %.0f, %.0f]\n  intensity:    %.2f\n"
			"  dispersion:   %d\n", light->pos.v4[0], light->pos.v4[1],
			light->pos.v4[2], light->rot.v4[0], light->rot.v4[1],
			light->rot.v4[2], light->color.v4[0] * 255,
			light->color.v4[1] * 255, light->color.v4[2] * 255,
			light->intensity, light->id);
		c++;
	}
}

void		print_parametrs(int fd, t_obj *obj)
{
	ft_fprintf(fd, "  position:     [%.2f, %.2f, %.2f]\n"
		"  rotation:     [%.2f, %.2f, %.2f]\n"
		"  color:        [%.0f, %.0f, %.0f]\n"
		"  emittance:    [%.0f, %.0f, %.0f]\n"
		"  reflective:   %.2f\n"
		"  specular:     %.2f\n", obj->pos.v4[0], obj->pos.v4[1],
		obj->pos.v4[2], obj->rot.v4[0], obj->rot.v4[1],
		obj->rot.v4[2], obj->mat.diff.v4[0] * 255,
		obj->mat.diff.v4[1] * 255, obj->mat.diff.v4[2] * 255,
		obj->mat.emittance.v4[0], obj->mat.emittance.v4[1],
		obj->mat.emittance.v4[2], obj->mat.reflection, obj->mat.specular);
	if (obj->id != ID_PLN && obj->id != ID_CUB)
		ft_fprintf(fd, "  radius:       %.2f\n", obj->radius);
	if (obj->id == ID_CUB || (!obj->infinite && (obj->id == ID_CON
		|| obj->id == ID_CYL)))
		ft_fprintf(fd, "  height:       %.2f\n", obj->height);
	if (obj->infinite && (obj->id == ID_CON || obj->id == ID_CYL))
		ft_fprintf(fd, "  infinite:     %.0f\n", obj->infinite);
}

void		print_tx(int fd, t_app *app, t_obj *obj)
{
	t_list	*lst;
	t_int	i;

	lst = app->tx_src_list;
	i = 0;
	while (lst && i < (int)app->op.tex_count)
	{
		if (obj->mat.diff_tex_id == i)
			ft_fprintf(fd, "  diff_texture: %s\n", lst->content);
		else if (obj->mat.refl_tex_id == i)
			ft_fprintf(fd, "  refl_texture: %s\n", lst->content);
		else if (obj->mat.spec_tex_id == i)
			ft_fprintf(fd, "  spec_texture: %s\n", lst->content);
		i++;
		lst = lst->next;
	}
}

void		printing_obj(int fd, t_app *app)
{
	t_obj	*obj;
	t_uint	c;

	c = 0;
	while (c < app->op.obj_count)
	{
		obj = &((t_obj*)app->ren.obj_buf.host)[c];
		ft_fprintf(fd, "- type: ");
		(obj->id == ID_SPH) ? ft_fprintf(fd, "sphere\n") : 0;
		(obj->id == ID_PLN) ? ft_fprintf(fd, "plane\n") : 0;
		(obj->id == ID_CYL) ? ft_fprintf(fd, "cylinder\n") : 0;
		(obj->id == ID_CON) ? ft_fprintf(fd, "cone\n") : 0;
		(obj->id == ID_CUB) ? ft_fprintf(fd, "cube\n") : 0;
		(obj->id == ID_PAR) ? ft_fprintf(fd, "paraboloid\n") : 0;
		(obj->id == ID_PCL) ? ft_fprintf(fd, "parabolic cylinder\n") : 0;
		(obj->id == ID_ELL) ? ft_fprintf(fd, "ellipse\n") : 0;
		(obj->id == ID_HCL) ? ft_fprintf(fd, "hyperbolic cylinder\n") : 0;
		(obj->id == ID_HTS) ? ft_fprintf(fd, "hyperboloid with two sheets\n")
			: 0;
		(obj->id == ID_HPR) ? ft_fprintf(fd, "hyperbolic paraboloid\n") : 0;
		print_parametrs(fd, obj);
		print_tx(fd, app, obj);
		c++;
	}
	close(fd);
}

int			save_scene(t_app *app)
{
	int		fd;
	char	name[150];

	file_name(name);
	(ft_strlen(name) + 4 < FILENAME_MAX) ? ft_sprintf(name, "%s.yml", name) : 0;
	if ((fd = open(name, O_RDWR | O_CREAT, 0666)) < 0)
		return (0);
	ft_fprintf(fd, "- type: camera\n  position:     [%.2f, %.2f, %.2f]\n"
		"  rotation:     [%.2f, %.2f, %.2f]\n  fov:          %.0f\n",
		app->cam.mtx.sC, app->cam.mtx.sD, app->cam.mtx.sE,
		app->cam.mtx.s4 * 360 / M_PI, app->cam.mtx.s5 * 360 / M_PI,
		app->cam.mtx.s6 * 360 / M_PI, app->cam.fov);
	(app->cam.sky != -1) ? ft_fprintf(fd, "  sky:          %s\n",
		app->tx_src_list->content) : 0;
	printing_light(fd, app);
	printing_obj(fd, app);
	return (1);
}
