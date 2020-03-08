/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/08 20:45:51 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/obj.h"
#include "../include/rt.h"

typedef struct  s_phelp
{
    char        str[NAME_MAX];
    int         len;
    void        *p;
    void        (*f)(char *, void *);
}               t_phelp;

#define PHELP(str, p, f) ((t_phelp){str, ft_strlen(str), p, f})

static int key_type(char *s)
{
	return (!ft_strncmp(s, "- type: ", 8));
}

void    parse_color(char *str, void *vp)
{
    t_color *p = vp;
    *p = array_color(str);
}

void    parse_vec3(char *str, void *vp)
{
    t_vec3 *p = vp;
    *p = array_attack(str);
}

void    parse_real(char *str, void *vp)
{
    t_real *p = vp;
    ignore_str(&str);
    *p = ptr_atoi(&str);
}

int is_valid_obj_name(char *str)
{
	return ((ft_strcmp(str, "plane") || \
		ft_strcmp(str, "cylinder") || ft_strcmp(str, "sphere") || \
		ft_strcmp(str, "cone")) && str[ft_strlen(str)] != '\0');
}

int		kill(char *message) // ++
{
	perror(message);
	exit(1);	
}

static void	ignore_str(char **ptr) // ++
{
	while (**ptr == ' ' || **ptr == '\t' || **ptr == ':' || ft_isalpha(**ptr))
		++(*ptr);
}

int		ptr_atoi_int(char **str, int fraction) // ++ 20_02
{
  int n;
  int sign;

  n = 0;
  sign = **str == '-' && !fraction ? -1 : 1;
  if (**str == '+' || (**str == '-' && !fraction))
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

t_real  ptr_atoi(char **str)
{
    int	w;
    int	f;

    w = ptr_atoi_int(str, 0);
    if ((**str) == '.')
    {
      if (!ft_isdigit(**str))
          kill("Error in number!");
      ++(**str);
      f = ptr_atoi_int(str, 1);
    }
		else
			f = 0;
    return ((t_real)w + f ? 1.0 / (t_real)f : 0);
}

t_color	array_color(char *s) // ++ 20_02
{
	int			i;
	int			r;
	int			g;
	int			b;

	ignore_str(&s);
	if (*s++ != '[' && s[ft_strlen(s) - 1] != ']' && s[ft_strlen(s)] != '\0')
		kill("Error in array!");
	i = 0;
	while (*s && i < 3)
	{
		++i;
		ignore_str(&s);
		if (i == 1)
			r = ptr_atoi(&s);
		else if (i == 2)
			g = ptr_atoi(&s);
		else if (i == 3)
			b = ptr_atoi(&s);
		else
			kill("Error in array!");
		ignore_str(&s);
		if (i < 3 && *s != ',')
			kill("Error in array coordinate!");
		++s;
		ignore_str(&s);
	}
	return (COLOR(r, g, b, 1));
}

t_vec3	array_attack(char *s) // ++ 20_02
{
	int			c;
	double	x;
	double	y;
	double	z;

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
	return (VEC({x, y, z}));
}

void	app_init(t_app *app) // + (to do ?)
{
	app->obj_sum = 0;
	app->obj_count = 0;
	app->light_sum = 0;
	app->light_count = 0;
//	app->obj = NULL;
//	app->light = NULL;
	app->cam.pos = VEC(0, 0, 0);
	app->cam.dir = VEC(0, 0, 0);
}

void	check_obj(t_app *app) // TO DO
{
	t_obj_list		*objects;
	t_light_list	*lights;

	lights = app->light_list;
	objects = app->obj_list;
	while (lights)
	{
			if (lights->light.intensity < 0)
				kill("Intensity must be positive!");
			lights = lights->next;
	}
	while (objects)
	{
		if (objects->obj.id != 2 && objects->obj.radius < 0)
			kill("Raduis so small!");
		if (objects->obj.mat.specular < 0)
			kill("Specularity must be positive!");
		if (objects->obj.mat.reflection < 0)
			kill("Reflective must be positive!");
		objects = objects->next;
	}
}


void	parser_obj(char **scn, t_app *app, int n)
{
    t_obj   ol;
    int     i;
    t_phelp phelp[10];
    int     phelp_len;

    phelp_len = 10;
    ft_bzero(&phelp, sizeof(t_phelp) * 10);

    // Add all fields here!

    phelp[0] = PHELP("  position:", &ol.pos, parse_vec3);
    phelp[1] = PHELP("  color:", &ol.mat.diffuse, parse_color);
    phelp[2] = PHELP("  rotation:", &ol.rot, parse_vec3);
    phelp[3] = PHELP("  radius:", &ol.rot, parse_real);
    phelp[4] = PHELP("  specular:", &ol.mat.specular, parse_real);
    phelp[5] = PHELP("  reflective:", &ol.mat.reflection, parse_real);
    phelp[6] = PHELP("  height:", &ol.height, parse_real);

    while (!key_type(scn[n]) && n <= app->lines)
    {
        if (!is_valid_obj_name(scn[n]))
			kill ("Error name obj");
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
        i = 0;
        while (i < phelp_len)
        {
            // Parse field with function from t_phelp
            if (!ft_strncmp(scn[n], phelp[i].str, phelp[i].len))
            {
                phelp[i].f(scn[n] + phelp[i].len, phelp[i].p);
                break;
            }
            i++;
        }
        check_obj(app);
        app->obj_sum++;
        ft_lstadd(&app->obj_list, ft_lstnew(&ol, sizeof(t_obj)));
        n = (ol.id > 2) ? n + 7 : n + 6;
    }
}

void	parser_light(char **scn, t_app *app, int n)
{
	t_light	ll;
    int     i;
    t_phelp phelp[5];
    int     phelp_len;

    phelp_len = 5;
    ft_bzero(&phelp, sizeof(t_phelp) * 5);

    phelp[0] = PHELP("  position:", &ll.pos, parse_vec3);
    phelp[1] = PHELP("  color:", &ll.color, parse_color);
    phelp[2] = PHELP("  direction:", &ll.dir, parse_vec3);
    phelp[3] = PHELP("  intensity:", &ll.intensity, parse_real);
  	
	while (key_type(scn[n]) && (!ft_strcmp(scn[n] + 8, T_LIGHT) \
		&& scn[n][ft_strlen(scn[n])] == '\0'))
	{
		if (!ft_strcmp(scn[1], "  dispersion:   1"))
            ll.id = ID_DIRECT;
        else if (!ft_strcmp(scn[1], "  dispersion:   2"))
            ll.id = ID_AMB;
        else if (!ft_strcmp(scn[1], "  dispersion:   3"))
            ll.id = ID_POINT;
        i = 0;
        while (i < phelp_len)
        {
            // Parse field with function from t_phelp
            if (!ft_strncmp(scn[n], phelp[i].str, phelp[i].len))
            {
                phelp[i].f(scn[n] + phelp[i].len, phelp[i].p);
                break;
            }
            i++;
        }
        check_obj(app);
		app->light_sum++;
		ft_lstadd(&app->light_list, ft_lstnew(&ll, sizeof(t_light)));
		n += 5;
	}
}

void	parser_cam(t_cam *cam, char **scn) // ++ 20_02
{
	if (!key_type(scn[0]) || ft_strcmp(scn[0] + 8, "camera"))
		kill("Error in str 'camera'");
	if (ft_strncmp(scn[1], "  position:", 11))
		kill("Error in str 'cam_pos'");
	cam->pos = array_attack(scn[1]);
	if (ft_strncmp(scn[2], "  direction:", 12))
		kill("Error in str 'cam_dir'");
	cam->dir = array_attack(scn[2]);
	if (ft_strncmp(scn[3], "  fov:", 6))
		kill("Error in str 'cam_fov'");
	ignore_str(&scn[3]);
	cam->fov = ptr_atoi(&scn[3]);
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
    if(!(scn = (char **)malloc(sizeof(char *) * (size + 2))))
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
	n = (app->light_sum) * 5 + 4; // номер строки, с которой начинаются объекты, если источников > 1
	parser_obj(app->scene, app, n);
}
