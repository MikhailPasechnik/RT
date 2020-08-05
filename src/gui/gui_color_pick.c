#include "gui.h"
#include "m3d.h"

unsigned int	gui_color_pick(t_color *clr, char* lbl, struct nk_context	*ctx)
{
	struct nk_colorf	tmp;

	tmp = (struct nk_colorf){clr->x, clr->y, clr->z};
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_label(ctx, lbl, NK_TEXT_LEFT);
	nk_layout_row_dynamic(ctx, 25, 1);
	if (nk_combo_begin_color(ctx, nk_rgb_cf(tmp), nk_vec2(nk_widget_width(ctx),400))) {
		nk_layout_row_dynamic(ctx, 120, 1);
		tmp = nk_color_picker(ctx, tmp, NK_RGB);
		nk_combo_end(ctx);
	}
	if (!CMP_CLR(tmp.r, tmp.g, tmp.b, clr->x, clr->y, clr->z))
	{
		*clr = COLOR(tmp.r, tmp.g, tmp.b, tmp.a);
		return (1);
	}
	return (0);
}

unsigned int	gui_gray_pick(t_real *clr, char* lbl, struct nk_context	*ctx)
{
	float	tmp;

	tmp = *clr;
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_label(ctx, lbl, NK_TEXT_LEFT);
	nk_layout_row_dynamic(ctx, 25, 1);
	tmp = nk_slide_float(ctx, 0, tmp, 1, 0.01f);
	if (tmp != *clr)
	{
		*clr = tmp;
		return (1);
	}
	return (0);
}
