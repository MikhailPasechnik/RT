/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:36:37 by bmahi             #+#    #+#             */
/*   Updated: 2020/06/26 22:47:00 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parser_cam(t_cam *cam, char **scn)
{
	t_vec3	pos;
	t_vec3	rot;

	if (!key_type(scn[0]) || ft_strcmp(scn[0] + 8, T_CAM))
		kill("Error in str 'camera'");
	if (ft_strncmp(scn[1], "  position:", 11))
		kill("Error in str 'cam_pos'");
	pos = array_attack(scn[1]);
	if (ft_strncmp(scn[2], "  rotation:", 11))
		kill("Error in str 'cam_rot'");
	rot = array_attack(scn[2]);
	if (ft_strncmp(scn[3], "  fov:", 6))
		kill("Error in str 'cam_fov'");
	m4_set_translate(&cam->mtx, &pos);
	m4_rotate(&cam->mtx, &rot);
	ignore_str(&scn[3]);
	cam->fov = ptr_atoi(&scn[3]);
	ft_printf("Camera :\n\tPosition :\t[%.2f, %.2f, %.2f]\n", pos.v4[0],
		pos.v4[1], pos.v4[2]);
	ft_printf("\tRotation :\t[%.2f, %.2f, %.2f]\n", rot.v4[0],
		rot.v4[1], rot.v4[2]);
	ft_printf("\tFOV :\t\t%.0f\n", cam->fov);
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
			kill("Malloc dropped!");
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
		kill("Open door!");
	app->scene = read_scene(fd, &(app->lines));
	close(fd);
	parser_cam(&app->cam, app->scene);
	parser_light(app->scene, app, 4);
	n = (app->op.light_count) * 6 + 4;
	parser_obj(app->scene, app, n);
	ft_printf("\nPositions of lights :\n");
	printing_light(app);
	ft_printf("\nPositions and parameters of objects :\n");
	printing_obj(app);
	printing_obj_r(app);
	if (!app->op.light_count || !app->op.obj_count)
		kill("Incomplete scene");
}
