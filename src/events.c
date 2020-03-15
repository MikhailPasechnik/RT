#include "rt.h"

void	on_mouse_move(SDL_MouseMotionEvent *event, t_app *app, int *changed)
{
	if (event->state & SDL_BUTTON_LMASK) // && SDL_GetModState() & KMOD_ALT)
	{
		nav_rotate_camera(&app->cam,
				&VEC(event->yrel * 0, event->xrel * 0, event->xrel * 1),
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
	SDL_DestroyTexture(app->canvas);
	app->canvas = NULL;
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
	const Uint8 *keyboard;

	keyboard = SDL_GetKeyboardState(NULL);
	if (event->keysym.sym == SDLK_ESCAPE)
	{
		app->quit = 1;
		return ;
	}
	else if (event->keysym.sym == SDLK_F12 && (*changed = 1))
		generate_scene(app);
	else if (event->keysym.sym == SDLK_w ||  event->keysym.sym == SDLK_s ||
	event->keysym.sym == SDLK_d || event->keysym.sym == SDLK_a ||
	event->keysym.sym == SDLK_q || event->keysym.sym == SDLK_e)
	{
		nav_move_camera(&app->cam, &VEC(
				(event->keysym.sym == SDLK_d || event->keysym.sym == SDLK_a)
				* (event->keysym.sym == SDLK_d ? 0.3 : -0.3),
				(event->keysym.sym == SDLK_q || event->keysym.sym == SDLK_e)
				* (event->keysym.sym == SDLK_q ? 0.3 : -0.3),
				(event->keysym.sym == SDLK_w || event->keysym.sym == SDLK_s)
				* (event->keysym.sym == SDLK_w ? 0.3 : -0.3)
				));
		app->cm_changed = 1;
		*changed = 1;
	}
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
