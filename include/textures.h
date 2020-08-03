/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:28:12 by cvernius          #+#    #+#             */
/*   Updated: 2020/08/03 19:33:19 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct			s_pix
{
	int					x;
	int					y;
}						t_pix;

typedef struct			s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef struct			s_texture
{
	int					*texture;
	int					size;
	int					cnt;
	t_color				average_color;
}						t_texture;

typedef struct			s_load_text
{
	unsigned char		*pixmap;
	int					nchannels;
	int					w;
	int					h;
}						t_load_text;
