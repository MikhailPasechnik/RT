#include "rt.h"

void	on_mouse_move(SDL_MouseMotionEvent *event, t_app *app, int *changed)
{
	if (event->state & SDL_BUTTON_LMASK) // && SDL_GetModState() & KMOD_ALT)
	{
		nav_rotate_camera(&app->cam,
				&VEC(event->yrel * 35, event->xrel * 35, 0),
				 &VEC(0, 0, 0)); // TODO: rotate around selection
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
	nav_move_camera(&app->cam, &VEC(0, 0, event->y > 0 ? -1 : 1));
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
