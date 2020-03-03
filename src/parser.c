/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/01 21:09:46 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int is_valid_obj_name(char *str)
{
	return ((ft_strncmp(str, "plane_", 6) || \
		ft_strncmp(str, "cylinder_", 9) || ft_strncmp(str, "sphere_", 7) || \
		ft_strncmp(str, "cone_", 5)) && (str[ft_strlen(str) - 1] != ':' \
		&& str[ft_strlen(str)] != '\0'));
}

int		kill(char *message) // ++
{
	perror(message);
	exit(1);	
}

t_vec	vec_init(double x, double y, double z) // ++
{
	t_vec	v_init;

	v_init.x_pos = x;
	v_init.y_pos = y;
	v_init.z_pos = z;
	return (v_init);
}

t_color	col_init(int r, int g, int b) // ++ 20_02
{
	t_color	col;

	r = (r < 0) ? 0 : r;
	r = (r > 255) ? 255 : r;
	g = (g < 0) ? 0 : g;
	g = (g > 255) ? 255 : g;
	b = (b < 0) ? 0 : b;
	b = (b > 255) ? 255 : b;
	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}

int		ptr_atoi(char **str) // ++ 20_02
{
  int n;
  int sign;

  n = 0;
  sign = **str == '-' ? -1 : 1;
  if (**str == '+' || **str == '-')
    ++(*str);
  if (!ft_isdigit(**str))
      kill("Error in number!");
  while (ft_isdigit(**str))
  {
    n = n * 10 + (**str - '0');
    ++(*str);
  }
  return (n * sign);
}

t_color	array_color(char *s) // ++ 20_02
{
	int		r;
	int		g;
	int		b;
	int		c;

	ignore_str(&s);
	if (*s++ != '[' && s[ft_strlen(s) - 1] != ']' && s[ft_strlen(s)] != '\0')
		kill("Error in array!");
	c = 0;
	while (*s && c < 3)
	{
		++c;
		ignore_str(&s);
		if (c == 1)
			r = ptr_atoi(&s);
		else if (c == 2)
			g = ptr_atoi(&s);
		else if (c == 3)
			b = ptr_atoi(&s);
		else
			kill("Error in array!");
		ignore_str(&s);
		if (c < 3 && *s != ',')
			kill("Error in array coordinate!");
		++s;
		ignore_str(&s);		
	}
	return (col_init(r, g, b));
}

void	ignore_str(char **ptr) // ++
{
	while (**ptr == ' ' || **ptr == '\t' || **ptr == ':' || ft_isalpha(**ptr))
		++(*ptr);
}

t_vec	array_attack(char *s) // ++ 20_02
{
	double	x;
	double	y;
	double	z;
	int			c;

	ignore_str(&s);
	if (*s++ != '[' && s[ft_strlen(s) - 1] != ']' && s[ft_strlen(s)] != '\0')
		kill("Error in array!");
	c = 0;
	while (*s && c < 3)
	{
		++c;
		ignore_str(&s);
		if (c == 1)
			x = (float)ptr_atoi(&s);
		else if (c == 2)
			y = (float)ptr_atoi(&s);
		else if (c == 3)
			z = (float)ptr_atoi(&s);
		else
			kill("Error in array!");
		ignore_str(&s);
		if (c < 3 && *s != ',')
			kill("Error in array coordinate!");
		++s;
		ignore_str(&s);		
	}
	return (vec_init(x, y, z));
}

void	app_init(t_app *app) // + (to do ?)
{
	app->obj_sum = 0;
	app->obj_count = 0;
	app->light_sum = 0;
	app->light_count = 0;
	app->obj = NULL;
	app->light = NULL;
	app->cam.pos = vec_init(0, 0, 0);
	app->cam.dir = vec_init(0, 0, 0);
	app->cam.rot = vec_init(0, 0, 0);
}

t_obj	*add_ol(t_app *app, t_obj *ol) // ++ 26_02
{
	t_obj	*lst;

	lst = app->obj;
	if (app->obj == NULL)
		return (ol);
	while (app->obj->next)
		app->obj = app->obj->next;
	app->obj->next = ol;
	return (lst);
}

t_light	*add_ll(t_app *app, t_light *ll) // ++ 26_02
{
	t_light	*lst;

	lst = app->light;
	if (app->light == NULL)
		return (ll);
	while (app->light->next)
		app->light = app->light->next;
	app->light->next = ll;
	return (lst);	
}

void	check_obj(t_app *app) // ++ 01_03
{
	t_obj		*obj;
	t_light	*light;

	light = app->light;
	obj = app->obj;
	while (light)
	{
			if (light->inten < 0)
				kill("Intensity must be positive!");
			light = light->next;
	}
	while (obj)
	{
		if (obj->name != 2 && obj->r < NLL)
			kill("Raduis so small!");
		if (obj->specul < 0)
			kill("Specularity must be positive!");
		if (obj->reflect < 0)
			kill("Reflective must be positive!");
		obj = obj->next;
	}
}

void	parser_obj(char **scn, t_app *app, int n) // ++ 01_03
{
	t_obj		*ol;
	
	while (n < app->lines)
	{
		if (!is_valid_obj_name(scn[n]))
			kill ("Error name obj");
		if (!(ol = (t_obj *)malloc(sizeof(t_obj))))
			kill("Malloc dropped!");
		if (!ft_strncmp(scn[n], "sphere_", 7))
			ol->name = ID_SPH;
		else if (!ft_strncmp(scn[n], "plane_", 6))
			ol->name = ID_PLN;
		else if (!ft_strncmp(scn[n], "cylinder_", 9))
			ol->name = ID_CYL;
		else if (!ft_strncmp(scn[n], "cone_", 5))
			ol->name = ID_CON;
		if (!ft_strncmp(scn[n + 1], "  position:", 11))
			ol->vec_pos = array_attack(scn[n + 1]);
		if (!ft_strncmp(scn[n + 2], "  color:", 8))
			ol->color = array_color(scn[n + 2]);
		if (!ft_strncmp(scn[n + 3], "  specular:", 11))
		{
			ignore_str(&scn[n + 3]);
			ol->specul = (float)ptr_atoi(&(scn[n + 3]));
		}
		if (!ft_strncmp(scn[n + 4], "  reflective:", 13))
		{
			ignore_str(&scn[n + 4]);
			ol->reflect = (float)ptr_atoi(&(scn[n + 4]));
		}
		if ((ol->name == 1) && !ft_strncmp(scn[n + 5], "  radius:", 9))
		{
			ignore_str(&(scn[n + 5]));
			ol->r = (float)ptr_atoi(&(scn[n + 5]));
		}
		if ((ol->name > 2) && !ft_strncmp(scn[n + 6], "  radius:", 9))
		{
			ignore_str(&(scn[n + 6]));
			ol->r = (float)ptr_atoi(&(scn[n + 6]));
		}
		if (!ft_strncmp(scn[n + 5], "  rotate:", 9) && ol->name != 1)
			ol->vec_rot = array_attack(scn[n + 5]);
		if (ol->name == 1)
			ol->vec_rot = vec_init(0, 0, 0);
		if (ol->name == 2)
			ol->r = 0;
		if (ol->name > 2)
			n++;
//		else
//			kill("Error in obj"); // добавить kill в случае ошибки!
		ol->next = NULL;
		check_obj(app);
		app->obj_sum++;
		app->obj = add_ol(app, ol);
		n += 6;
	}
}

void	parser_light(char **scn, t_app *app, int n)
{
	t_light	*ll;
	
	while (!ft_strncmp(scn[n], "light_", 6) &&
		(scn[n][ft_strlen(scn[n]) - 1] == ':' && scn[n][ft_strlen(scn[n])] == '\0'))
	{
		if (!(ll = (t_light *)malloc(sizeof(t_light))))
			kill("Malloc dropped!");
		if (!ft_strncmp(scn[n + 1], "  position:", 11))
			ll->vec_pos = array_attack(scn[n + 1]);
		if (!ft_strncmp(scn[n + 2], "  color:", 8)) 
			ll->color = array_color(scn[n + 2]);
		if (!ft_strncmp(scn[n + 3], "  intensity:", 12))
		{
			ignore_str(&scn[n + 3]);
			ll->inten = (float)ptr_atoi(&scn[n + 3]) / 100;
		}
		else
			kill("Error in light");
		ll->next = NULL;
		check_obj(app);
		app->light_sum++;
		app->light = add_ll(app, ll);
		n += 4;
	}
}

void	parser_cam(t_cam *cam, char **scn) // ++ 20_02
{
	if (ft_strcmp(scn[0], "camera:"))
		kill("Error in str 'camera'");
	if (ft_strncmp(scn[1], "  position:", 11))
		kill("Error in str 'cam_pos'");
	cam->pos = array_attack(scn[1]);
	if (ft_strncmp(scn[2], "  direction:", 12))
		kill("Error in str 'cam_dir'");
	cam->dir = array_attack(scn[2]);
}

char	**read_scene(int fd, int *lines) // ++ 01_03
{
	char 	*gnled;
  char 	**arr_old = NULL;
  char 	**scn;
  int 	size = 0;
  int 	i;

	while (get_next_line(fd, &gnled) > 0)
  {
    scn = (char **)malloc(sizeof(char *) * (size + 2));
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

void	parser(t_app *app, char *scene) // ++ 01_03
{
	int	n;
	int	fd;

	n = 0;
	app->lines = 0;
	if ((fd = open(scene, O_RDONLY)) < 0)
		kill("Open door!");
	app->scene = read_scene(fd, &(app->lines));
	app_init(app);
	parser_cam(&app->cam, app->scene);
	parser_light(app->scene, app, 3);
	n = (app->light_sum) * 4 + 3; // номер строки, с которой начинаются объекты, если источников > 1
	parser_obj(app->scene, app, n);
}
