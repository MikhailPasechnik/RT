#include "controller.h"

void		on_controller_event(SDL_Event *event, t_controller *ctr, int *changed)
{
	if (event->type == SDL_KEYUP || event->type == SDL_KEYDOWN)
		on_controller_state(&event->key, ctr, changed);
	else if (event->type == SDL_MOUSEBUTTONDOWN ||
			 event->type == SDL_MOUSEBUTTONUP)
		on_controller_click(&event->button, ctr, changed);
}
void		on_controller_state(SDL_KeyboardEvent *event, t_controller *ctr, int *changed)
{
	int	mouse[2];

	if (event->keysym.sym == SDLK_SPACE && !event->repeat && event->type == SDL_KEYDOWN)
	{
		SDL_GetMouseState(&mouse[0], &mouse[1]);
		if (mouse[0] || mouse[1])
		{
			ctr->at.x = mouse[0] - 25;
			ctr->at.y = mouse[1] - 25;
		}
		ctr->active = 1;
		*changed = 1;
	}
	else if (event->keysym.sym == SDLK_SPACE && event->type == SDL_KEYUP)
	{
		reset_controller(ctr);
		*changed = 1;
	}
}

int			is_controller_active()
{
	const Uint8 *keys;

	keys = SDL_GetKeyboardState(NULL);
	return (keys[SDL_SCANCODE_SPACE]);
}

void		on_controller_interact(SDL_MouseMotionEvent *event, t_controller *ctr, int *changed)
{
	if (!ctr->active)
		return ;
}

int 		get_controller_zone(double angle)
{
	ft_printf("angle: %f\n", angle);
	if (angle > 30 && angle <= 150)
		return (2);
	else if ((angle < 30 && angle > 0) || (angle < 0 && angle > -90))
		return (1);
	else if ((angle > 150 && angle > 0) || (angle < 0 && angle < -90))
		return (3);
	return (0);
}

void		on_controller_click(SDL_MouseButtonEvent *event, t_controller *ctr, int *changed)
{
	int		w;
	int		h;

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_GetWindowSize(ctr->win, &w, &h);
		ctr->zone = get_controller_zone(radToDeg(atan2(
			(((double)event->y - h / 2.0) - ((double)ctr->at.y - h / 2.0)) * -1,
			((double)event->x  - w / 2.0) - ((double)ctr->at.x - w / 2.0)
	 	)));
		ft_printf("zone: %d\n", ctr->zone);
	}
}

void		draw_controller(t_controller *controller, SDL_Renderer *renderer)
{
	if (is_controller_active())
		SDL_RenderCopy(renderer, controller->texture, NULL, &controller->at);
}

void		reset_controller(t_controller *controller)
{
	controller->active = 0;
	controller->zone = 0;
	controller->at = (SDL_Rect){.x=0, .y=0, .w=50, .h=50};
	SDL_GetWindowSize(controller->win, &controller->at.x, &controller->at.y);
	controller->at.x = controller->at.x / 2 - 25;
	controller->at.y = controller->at.y / 2 - 25;
}

int			init_controller(t_controller *controller, SDL_Renderer *renderer, SDL_Window *window)
{
	ft_bzero(controller, sizeof(t_controller));
	controller->texture = IMG_LoadTexture(renderer, CTR_TEXTURE);
	controller->win = window;
	reset_controller(controller);
	return (controller->texture != NULL && controller->win != NULL);
}

void		del_controller(t_controller *controller)
{
	controller->texture ? SDL_DestroyTexture(controller->texture) : 0;
}
