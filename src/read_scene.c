/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:36:37 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/01 22:14:39 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		parser_cam(t_cam *cam, char **scn, t_app *app)
{
	t_vec3	pos;
	t_vec3	rot;
	int 	n;

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
	ignore_str(&scn[n], 0);
	cam->fov = ptr_atoi(&scn[n++]);
	if (!(ft_strncmp(scn[n], "  sky:", 6)))
		parse_texture(scn[n++] + 6, &cam->sky, app);
	m4_set_translate(&cam->mtx, &pos);
	m4_rotate(&cam->mtx, &rot);
	return (n);
}

char	**read_scene(int fd, int *lines)
{
	char	*gnled;
	char	**arr_old;
	char	**scn;
	int		size;
	int		i;

	arr_old = NULL;
	size = 0;
	while (get_next_line(fd, &gnled) > 0)
	{
		if (!(scn = (char **)malloc(sizeof(char *) * (size + 2))))
			kill("Error allocating memory!");
		i = 0;
		while (i < size)
		{
			scn[i] = arr_old[i];
			++i;
		}
		scn[size++] = gnled++;
		scn[size] = NULL;
		free(arr_old);
		arr_old = scn;
		(*lines)++;
	}
	return (scn);
}

void	parser(t_app *app, char *scene)
{
	int	n;
	int	fd;

	n = 0;
	app->lines = 0;
	if ((fd = open(scene, O_RDONLY)) < 0)
		kill("Can't open file!");
	app->scene = read_scene(fd, &(app->lines));
	close(fd);
	n = parser_cam(&app->cam, app->scene, app);
	parser_light(app->scene, app, n);
	n = (app->op.light_count) * 6 + n;
	parser_obj(app->scene, app, n);
	if (!app->op.light_count || !app->op.obj_count)
		kill("Incomplete scene.");
}
