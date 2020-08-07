#include "rt.h"

static void		delete_linked_list(t_list *lst)
{
	while (lst)
	{
		free(lst->content);
		lst = lst->next;
	}
}

void			app_delete_linked_lists(t_app *app)
{
	delete_linked_list(app->light_list);
	delete_linked_list(app->tx_info_list);
	delete_linked_list(app->tx_list);
	delete_linked_list(app->tx_src_list);
	delete_linked_list(app->obj_list);
}
