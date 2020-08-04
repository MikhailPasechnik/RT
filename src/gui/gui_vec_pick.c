#include "gui.h"
#include "m3d.h"

unsigned int	gui_vec_pick(t_vec3 *vec, char* lbl, struct nk_context	*ctx, char prefix)
{
	t_vec3	tmp;
	char	p[4];

	tmp = *vec;
	p[0] = prefix;
	p[2] = ':';
	p[3] = '\0';
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_label(ctx, lbl, NK_TEXT_LEFT);
	nk_layout_row_dynamic(ctx, 25, 1);
	p[1] = 'X';
	tmp.x = nk_propertyf(ctx, p, -9999, tmp.x, 9999, 0.5f,0.25f);
	p[1] = 'Y';
	tmp.y = nk_propertyf(ctx, p, -9999, tmp.y, 9999, 0.5f,0.25f);
	p[1] = 'Z';
	tmp.z = nk_propertyf(ctx, p, -9999, tmp.z, 9999, 0.5f,0.25f);
	if (!CMP_VEC((&tmp), vec))
	{
		*vec = tmp;
		return (1);
	}
	return (0);
}