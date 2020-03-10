#include "rt.h"

void	on_mouse_move(SDL_MouseMotionEvent *event, t_app *app, int *changed)
{
}

void	on_window_size_change(SDL_WindowEvent *event, t_app *app, int *changed)
{
	(void)event;
	SDL_GetWindowSize(app->win, &app->op.width, &app->op.height);
	rt_set_rect(&app->rect, 0, 0, app->op.width, app->op.height);
	*changed = 1;
}

void	on_mouse_wheel(SDL_MouseWheelEvent *event, t_app *app, int *changed)
{
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
	if (event->state == SDL_PRESSED)
		app->mouse_flag |= event->state;
	else if (event->state == SDL_RELEASED)
		app->mouse_flag &= ~event->state;
}


void	on_mouse_focus(SDL_Event *event, t_app *app, int *changed)
{
	if (event->type == SDL_WINDOWEVENT_ENTER)
	{}
	else if (event->type == SDL_WINDOWEVENT_LEAVE)
		app->mouse_flag = 0;
}
