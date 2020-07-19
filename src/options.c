#include "rt.h"

void	init_options(t_options *op) {
	op->height = RT_WIN_HEIGHT;
	op->width = RT_WIN_WIDTH;
	op->selection = -1;
	op->background_color = VEC(44 / 255.0, 44 / 255.0, 44 / 255.0);
}
