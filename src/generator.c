#include "rt.h"

static int		rand_interval(int min, int max)
{
	return  (rand() % (max - min + 1)) + min;
}

static void	fake_light(t_light *l, t_int id)
{
	l->id = id;
	l->pos = VEC(
			rand_interval(-10, 10),
			rand_interval(-10, 10),
			rand_interval(7, 25)
	);
	l->dir = VEC(
			rand_interval(-100, 100),
			rand_interval(-100, 100),
			rand_interval(-100, 100)
	);
	v3_norm(&l->dir, &l->dir);
	l->color = VEC(
			rand_interval(0, 255),
			rand_interval(0, 255),
			rand_interval(0, 255)
	);
	v3_mull_s(&l->color, 1 / 255.0, &l->color);
	l->intensity = rand_interval(0, 100) / 100.0;
}

static void	fake_obj(t_obj *s, t_int id)
{
	s->pos = VEC(
			rand_interval(-10, 10),
			rand_interval(-10, 10),
			rand_interval(7, 25)
	);
	s->rot = VEC(
			rand_interval(-100, 100),
			rand_interval(-100, 100),
			rand_interval(-100, 100)
	);
	v3_norm(&s->rot, &s->rot);
	s->radius = rand_interval(1, 5);
	s->height = rand_interval(1, 5);
	s->id = id;
	s->symbol = rand_interval(49, 100);
	s->mat.ior = rand_interval(0, 255) / 255.0;
	s->mat.fresnel = rand_interval(0, 255) / 255.0;
	s->mat.reflection = rand_interval(0, 255) / 255.0;
	s->mat.refraction = rand_interval(0, 255) / 255.0;
	s->mat.specular = rand_interval(0, 255) / 255.0;
	s->mat.diffuse = VEC(
			rand_interval(0, 255),
			rand_interval(0, 255),
			rand_interval(0, 255)
	);
	v3_mull_s(&s->mat.diffuse, 1 / 255.0, &s->mat.diffuse);
}

static void ground_plane(t_obj *o)
{
	fake_obj(0, ID_PLN);
	o->rot = VEC(0, 0, -1);
	o->rot = VEC(0, 1, 0);
}

static void del_obj(void *o, size_t _)
{
	ft_memdel(&o);
}

void	generate_scene(t_app *app)
{
	int		s;
	t_obj	o;
	t_light	l;

	app->cam = (t_cam){
			.fov=80
	};
	ft_bzero(&app->cam.mtx, sizeof(t_mat4));
	m4_set_rotation(&app->cam.mtx, &VEC(0,0,0));
	app->op = (t_options){
			.background_color = VEC(0,0,0),
			.reflection_depth = 0,
			.obj_count = 0,
			.light_count = 0,
			.width = app->op.width,
			.height = app->op.height
	};
	ft_lstdel(&app->light_list, del_obj);
	ft_lstdel(&app->obj_list, del_obj);
	// ground_plane(&o);
	// ft_lstadd(&app->obj_list, ft_lstnew(&o, sizeof(t_obj)));
	// app->op.scene_size++;
	s = rand_interval(70, 150);
	while(s--)
	{
		fake_obj(&o, ID_SPH);
		ft_lstadd(&app->obj_list, ft_lstnew(&o, sizeof(t_obj)));
		app->op.obj_count++;
	}
	s = rand_interval(1, 3);
	while(s--)
	{
		fake_light(&l, ID_SPH);
		ft_lstadd(&app->light_list, ft_lstnew(&l, sizeof(t_light)));
		app->op.light_count++;
	}
	app->ol_changed = 1;
	app->ll_changed = 1;
	app->op_changed = 1;
	app->cm_changed = 1;
}
