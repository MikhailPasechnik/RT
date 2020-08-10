#include "rt.h"

static void		delete_linked_list(t_list **lst)
{
	t_list *it;
	t_list *tmp;

	it = *lst;
	while (it)
	{
		free(it->content);
		tmp = it;
		it = tmp->next;
		free(tmp);
	}
	*lst = NULL;
}

void			app_delete_linked_lists(t_app *app)
{
	delete_linked_list(&app->light_list);
	delete_linked_list(&app->tx_info_list);
	delete_linked_list(&app->tx_list);
	delete_linked_list(&app->tx_src_list);
	delete_linked_list(&app->obj_list);
}
