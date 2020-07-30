/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/07/08 19:43:55 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLLER_H
# define CONTROLLER_H
# include "SDL.h"
# include "SDL_image.h"
# include "libft.h"
# include "ft_printf.h"
# include "math.h"

# define CTR_TEXTURE "resources/textures/xyz_cube.png"
# define PI   3.14159265358979f
# define radToDeg(x) ((x)*180.f/PI)

typedef struct	s_controller {
	int					active;
	int					zone;
	SDL_Texture			*texture;
	SDL_Window 			*win;
	SDL_Rect			at;
}				t_controller;

int				init_controller(t_controller* controller, SDL_Renderer *renderer, SDL_Window *window);
void			del_controller(t_controller* controller);
void			reset_controller(t_controller* controller);
int				is_controller_active();
int				get_controller_zone(double angle);
void			draw_controller(t_controller* controller, SDL_Renderer *renderer);

void			on_controller_event(SDL_Event *event, t_controller *ctr, int *changed);
void			on_controller_state(SDL_KeyboardEvent *event, t_controller *ctr, int *changed);
void			on_controller_interact(SDL_MouseMotionEvent *event, t_controller *ctr, int *changed);
void			on_controller_click(SDL_MouseButtonEvent *event, t_controller *ctr, int *changed);

#define CONTROLLER_H

#endif //CONTROLLER_H
