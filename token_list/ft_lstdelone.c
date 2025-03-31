
#include "tokenlist.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	if (lst->content)
		del(lst->content);
	if (lst->result)
		del(lst->result);
	free(lst);
}
