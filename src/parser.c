/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/17 00:18:26 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include   "../include/obj.h"
#include   "../include/rt.h"

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

void    parse_id(char *str, void *vp)
{
    t_int   *id = vp;
    ignore_str(&str);
    *id = ptr_atoi(&str);
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

int		is_valid_light_name(char *str)
{
    return (!ft_strcmp(str, T_LIGHT) && str[ft_strlen(str)] == '\0');
}

int		is_valid_obj_name(char *str)
{
	return ((!ft_strcmp(str, T_CON) || !ft_strcmp(str, T_CUB) \
	    || !ft_strcmp(str, T_CYL) || !ft_strcmp(str, T_PLN) \
	    || !ft_strcmp(str, T_SPH)) && str[ft_strlen(str)] == '\0');
}

int		kill(char *message)
{
    perror(message);
	exit(1);
}

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

t_real  ptr_atoi(char **str)
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
	return (COLOR(r / 255.0, g / 255.0, b / 255.0, 1));
}

t_vec3	array_attack(char *s)
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
			x = ptr_atoi(&s);
		else if (c == 2)
			y = ptr_atoi(&s);
		else if (c == 3)
			z = ptr_atoi(&s);
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

void	app_init(t_app *app)
{
	app->op.obj_count = 0;
	app->op.light_count = 0;
}

void	check_obj(t_app *app)
{
	t_obj_list		*objects;
	t_light_list	*lights;
	t_obj			*obj;
	t_light			*lig;

	lights = app->light_list;
	objects = app->obj_list;
	while (lights)
	{
		lig = lights->content;
		if (lig->intensity < 0)
			kill("Intensity must be positive!");
        if (lig->id < ID_DIRECT || lig->id > ID_AMB)
            kill("Dispersion must be 1, 2 or 3!");
		lights = lights->next;
	}
	while (objects)
	{
		obj = objects->content;
		if (obj->id == 1)
		    obj->rot = VEC(0, 0, 0);
		if (obj->id != 2 && obj->id != 5 && obj->radius < 0)
			kill("Raduis so small!");
		if (obj->mat.specular < 0)
			kill("Specularity must be positive!");
		if (obj->mat.reflection < 0)
			kill("Reflective must be positive!");
		objects = objects->next;
	}
}

void	parser_obj(char **scn, t_app *app, int n)
{
    t_obj   ol;
    int     i;
    t_phelp phelp[7];
    int     phelp_len;

    phelp_len = 7;
    ft_bzero(&phelp, sizeof(t_phelp) * 7);

    phelp[0] = PHELP("  position:", &ol.pos, parse_vec3);
    phelp[1] = PHELP("  color:", &ol.mat.diffuse, parse_color);
    phelp[2] = PHELP("  rotation:", &ol.rot, parse_vec3);
    phelp[3] = PHELP("  radius:", &ol.radius, parse_real);
    phelp[4] = PHELP("  specular:", &ol.mat.specular, parse_real);
    phelp[5] = PHELP("  reflective:", &ol.mat.reflection, parse_real);
    phelp[6] = PHELP("  height:", &ol.height, parse_real);

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
                    break;
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
    int     i;
    t_phelp phelp[5];
    int     phelp_len;

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
                    break;
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
}

char	**read_scene(int fd, int *lines)
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

void	parser(t_app *app, char *scene)
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
	parser_light(app->scene, app, 4);
	n = (app->op.light_count) * 6 + 4;
	parser_obj(app->scene, app, n);
}
