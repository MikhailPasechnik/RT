/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:36:37 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/10 16:58:20 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		parser_cam(t_cam *cam, char **scn, t_app *app)
{
	t_vec3	pos;
	t_vec3	rot;
	int		n;
	char	*s;

	n = 0;
	cam->sky = -1;
	if (!key_type(scn[n]) || ft_strcmp(scn[n++] + 8, T_CAM))
		kill("Usage :  - type: camera");
	if (ft_strncmp(scn[n], "  position:", 11))
		kill("Usage :  position: [x, y, z]");
	pos = array_attack(scn[n++]);
	if (ft_strncmp(scn[n], "  rotation:", 11))
		kill("Usage :  rotation: [x, y, z]");
	rot = array_attack(scn[n++]);
	if (ft_strncmp(scn[n], "  fov:", 6))
		kill("Usage :  fov: 60");
	s = scn[n++] + 6;
	ignore_str(&s, 0);
	cam->fov = ptr_atoi(&s);
	if (!(ft_strncmp(scn[n], "  sky:", 6)))
		parse_texture(scn[n++] + 6, &cam->sky, app);
	m4_set_translate(&cam->mtx, &pos);
	m4_rotate(&cam->mtx, &rot);
	return (n);
}

char	**read_scene(char *scene_file, int *lines)
{
	char **split;
	char *src;

	src = fio_read_file(scene_file, NULL);
	split = ft_strsplit(src, '\n');
	while (split && split[*lines])
		(*lines)++;
	src ? free(src) : 0;
	return (split);
}

void	parser(t_app *app, char *scene)
{
	int	n;

	app->lines = 0;
	app->scene = read_scene(scene, &(app->lines));
	if (!app->scene)
		kill("Scene read failed.");
	n = parser_cam(&app->cam, app->scene, app);
	parser_light(app->scene, app, n);
	n = (app->op.light_count) * 6 + n;
	parser_obj(app->scene, app, n);
	if (!app->op.light_count || !app->op.obj_count)
		kill("Incomplete scene.");
}
