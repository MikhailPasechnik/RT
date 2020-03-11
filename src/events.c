#include "rt.h"

void	on_mouse_move(SDL_MouseMotionEvent *event, t_app *app, int *changed)
{
	if (event->state & SDL_BUTTON_LMASK && SDL_GetModState() & KMOD_CTRL)
	{
		v3_add(&app->cam.dir, &VEC(event->yrel * 0.7, event->xrel * 0.7, 0),
				&app->cam.dir);
		app->cm_changed = 1;
		*changed = 1;
	}
}

void	on_window_size_change(SDL_WindowEvent *event, t_app *app, int *changed)
{
	(void)event;
	SDL_GetWindowSize(app->win, (int *)&app->op.width, (int *)&app->op.height);
	rt_set_rect(&app->rect, 0, 0, app->op.width, app->op.height);
	app->op_changed = 1;
	*changed = 1;
}

void	on_mouse_wheel(SDL_MouseWheelEvent *event, t_app *app, int *changed)
{
	t_mat4 m;
	t_vec3 v;

	m4_identity(&m);
	m4_set_rotation(&m, &app->cam.dir);
	v3_mull_s(&VEC(m.s8, m.s9,m.sA), event->y > 0 ? 1 : -1, &v);
	v3_add(&app->cam.pos, &v, &app->cam.pos);
	app->cm_changed = 1;
	*changed = 1;
}

void	on_key_press(SDL_KeyboardEvent *event, t_app *app, int *changed)
{
	if (event->keysym.sym == SDLK_ESCAPE)
	{
		app->quit = 1;
		return ;
	}
	else if (event->keysym.sym == SDLK_F12 && (*changed = 1))
		generate_scene(app);
}


void	on_mouse_button(SDL_MouseButtonEvent *event, t_app *app, int *changed)
{
//	if (event->state == SDL_PRESSED)
//
//	else if (event->state == SDL_RELEASED)
//
}


void	on_mouse_focus(SDL_Event *event, t_app *app, int *changed)
{
}
