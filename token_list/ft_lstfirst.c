
#include "../minishell.h"

t_list	*ft_lstfirst(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->prev != NULL && lst->prev->type != PIPE)
		lst = lst->prev;
	return (lst);
}
