///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   parser.c                                           :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
///*   Updated: 2020/03/01 21:09:46 by bmahi            ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "../include/obj.h"
//#include "../include/rt.h"
//
//int is_valid_obj_name(char *str)
//{
//	return ((ft_strncmp(str, "plane_", 6) || \
//		ft_strncmp(str, "cylinder_", 9) || ft_strncmp(str, "sphere_", 7) || \
//		ft_strncmp(str, "cone_", 5)) && (str[ft_strlen(str) - 1] != ':' \
//		&& str[ft_strlen(str)] != '\0'));
//}
//
//int		kill(char *message) // ++
//{
//	perror(message);
//	exit(1);
//}
//
//void	ignore_str(char **ptr) // ++
//{
//	while (**ptr == ' ' || **ptr == '\t' || **ptr == ':' || ft_isalpha(**ptr))
//		++(*ptr);
//}
//
//
//int		ptr_atoi_int(char **str, int fraction) // ++ 20_02
//{
//  int n;
//  int sign;
//
//  n = 0;
//  sign = **str == '-' && !fraction ? -1 : 1;
//  if (**str == '+' || (**str == '-' && !fraction))
//    ++(*str);
//  if (!ft_isdigit(**str))
//      kill("Error in number!");
//  while (ft_isdigit(**str))
//  {
//    n = n * 10 + (**str - '0');
//    ++(*str);
//  }
//  return (n * sign);
//}
//
//t_real  ptr_atoi(char **str)
//{
//    int w;
//    int f;
//
//    w = ptr_atoi_int(str, 0);
//    if ((**str) == '.')
//    {
//        if (!ft_isdigit(**str))
//            kill("Error in number!");
//        ++(**str);
//        f = ptr_atoi_int(str, 1);
//    } else
//        f = 0;
//    return ((t_real)w + 1.0 / (t_real)f);
//}
//
//t_color	color_attack(char *s) // ++ 20_02
//{
//	t_color	c;
//	int		i;
//
//	ignore_str(&s);
//	if (*s++ != '[' && s[ft_strlen(s) - 1] != ']' && s[ft_strlen(s)] != '\0')
//		kill("Error in array!");
//	i = 0;
//	c = COLOR(0, 0, 0, 0);
//	while (*s && i < 3)
//	{
//		++i;
//		ignore_str(&s);
//		if (i == 1)
//			c.x = ptr_atoi(&s);
//		else if (i == 2)
//			c.y = ptr_atoi(&s);
//		else if (i == 3)
//			c.z = ptr_atoi(&s);
//		else if (i == 4)
//			c.w = ptr_atoi(&s);
//		else
//			kill("Error in array!");
//		ignore_str(&s);
//		if (i < 3 && *s != ',')
//			kill("Error in array coordinate!");
//		++s;
//		ignore_str(&s);
//	}
//	return (c);
//}
//
//t_vec3	array_attack(char *s) // ++ 20_02
//{
//	t_vec3		v;
//	int			c;
//
//	ignore_str(&s);
//	if (*s++ != '[' && s[ft_strlen(s) - 1] != ']' && s[ft_strlen(s)] != '\0')
//		kill("Error in array!");
//	c = 0;
//	v = VEC(0, 0, 0);
//	while (*s && c < 3)
//	{
//		++c;
//		ignore_str(&s);
//		if (c == 1)
//			v.x = ptr_atoi(&s);
//		else if (c == 2)
//			v.y = ptr_atoi(&s);
//		else if (c == 3)
//			v.z = ptr_atoi(&s);
//		else
//			kill("Error in array!");
//		ignore_str(&s);
//		if (c < 3 && *s != ',')
//			kill("Error in array coordinate!");
//		++s;
//		ignore_str(&s);
//	}
//	return (v);
//}
//
//t_obj	*add_ol(t_app *app, t_obj *ol) // ++ 26_02
//{
//	t_obj	*lst;
//
//	lst = app->obj_list;
//	if (app->obj_list == NULL)
//		return (ol);
//	while (app->obj_list->next)
//		app->obj_list = app->obj_list->next;
//	app->obj_list->next = ol;
//	return (lst);
//}
//
//t_light	*add_ll(t_app *app, t_light *ll) // ++ 26_02
//{
//	t_light	*lst;
//
//	lst = app->light_list;
//	if (app->light_list == NULL)
//		return (ll);
//	while (app->light_list->next)
//		app->light_list = app->light_list->next;
//	app->light_list->next = ll;
//	return (lst);
//}
//
//void	check_obj(t_app *app) // ++ 01_03
//{
//}
//
//void	parser_obj(char **scn, t_app *app, int n) // ++ 01_03
//{
//	t_obj		o;
//	while (n < app->lines)
//	{
//        ft_bzero(&o, sizeof(t_obj));
//		if      (!ft_strcmp(scn[n], "type: "T_SPH))
//            o.id = ID_SPH;
//		else if (!ft_strcmp(scn[n], "type: "T_PLN))
//            o.id = ID_PLN;
//		else if (!ft_strcmp(scn[n], "type: "T_CYL))
//            o.id = ID_CYL;
//		else if (!ft_strcmp(scn[n], "type: "T_CON))
//            o.id = ID_CON;
//		else if (!ft_strcmp(scn[n], "position: "))
//            o.pos = array_attack(scn[n + 1]);
//		else if (!ft_strncmp(scn[n + 2], "  diffuse:", 8))
//            o.mat.diffuse = color_attack(scn[n + 2]);
//		if (!ft_strncmp(scn[n + 3], "  specular:", 11))
//		{
//			ignore_str(&scn[n + 3]);
//            o.mat.specular = ptr_atoi(&(scn[n + 3]));
//		}
//		if (!ft_strncmp(scn[n + 4], "  reflective:", 13))
//		{
//			ignore_str(&scn[n + 4]);
//            o.mat.specular = ptr_atoi(&(scn[n + 4]));
//		}
//		if ((o.name == 1) && !ft_strncmp(scn[n + 5], "  radius:", 9))
//		{
//			ignore_str(&(scn[n + 5]));
//            o.r = ptr_atoi(&(scn[n + 5]));
//		}
//		if ((o.name > 2) && !ft_strncmp(scn[n + 6], "  radius:", 9))
//		{
//			ignore_str(&(scn[n + 6]));
//            o.r = ptr_atoi(&(scn[n + 6]));
//		}
//		if (!ft_strncmp(scn[n + 5], "  rotate:", 9) && o.name != 1)
//            o.rot = array_attack(scn[n + 5]);
//		if (o.name == 1)
//            o.rot = VEC(0, 0, 0);
//		if (o.name == 2)
//            o.r = 0;
//		if (o.name > 2)
//			n++;
////		else
////			kill("Error in obj"); // добавить kill в случае ошибки!
//		check_obj(app);
//		app->obj_count++;
//		add_ol(app, &o);
//		n += 6;
//	}
//}
//
//void	parser_light(char **scn, t_app *app, int n)
//{
//	t_light	*ll;
//
//	while (!ft_strncmp(scn[n], "light_", 6) &&
//		(scn[n][ft_strlen(scn[n]) - 1] == ':' && scn[n][ft_strlen(scn[n])] == '\0'))
//	{
//		if (!(ll = (t_light *)malloc(sizeof(t_light))))
//			kill("Malloc dropped!");
//		if (!ft_strncmp(scn[n + 1], "  position:", 11))
//			ll->vec_pos = array_attack(scn[n + 1]);
//		if (!ft_strncmp(scn[n + 2], "  color:", 8))
//			ll->color = color_attack(scn[n + 2]);
//		if (!ft_strncmp(scn[n + 3], "  intensity:", 12))
//		{
//			ignore_str(&scn[n + 3]);
//			ll->intensity = ptr_atoi(&scn[n + 3]) / 100;
//		}
//		else
//			kill("Error in light");
//		ll->next = NULL;
//		check_obj(app);
//		app->light_count++;
//		app->light_list = add_ll(app, ll);
//		n += 4;
//	}
//}
//
//void	parser_cam(t_cam *cam, char **scn) // ++ 20_02
//{
//	if (ft_strcmp(scn[0], "camera:"))
//		kill("Error in str 'camera'");
//	if (ft_strncmp(scn[1], "  position:", 11))
//		kill("Error in str 'cam_pos'");
//	cam->pos = array_attack(scn[1]);
//	if (ft_strncmp(scn[2], "  direction:", 12))
//		kill("Error in str 'cam_dir'");
//	cam->dir = array_attack(scn[2]);
//}
//
//char	**read_scene(int fd, int *lines) // ++ 01_03
//{
//	char 	*gnled;
//  char 	**arr_old = NULL;
//  char 	**scn;
//  int 	size = 0;
//  int 	i;
//
//	while (get_next_line(fd, &gnled) > 0)
//  {
//    if(!(scn = (char **)malloc(sizeof(char *) * (size + 2))))
//		kill("Malloc dropped!");
//    i = 0;
//    while (i < size)
//		{
//			scn[i] = arr_old[i];
//			++i;
//		}
//		scn[size++] = gnled++;
//    scn[size] = NULL;
//    free(arr_old);
//    arr_old = scn;
//		(*lines)++;
//	}
//	return (scn);
//}
//
//void	parser(t_app *app, char *scene) // ++ 01_03
//{
//	int	n;
//	int	fd;
//
//	n = 0;
//	app->lines = 0;
//	if ((fd = open(scene, O_RDONLY)) < 0)
//		kill("Open door!");
//	app->scene = read_scene(fd, &(app->lines));
//	app_init(app);
//	parser_cam(&app->cam, app->scene);
//	parser_light(app->scene, app, 3);
//	n = (app->light_count) * 4 + 3; // номер строки, с которой начинаются объекты, если источников > 1
//	parser_obj(app->scene, app, n);
//}
