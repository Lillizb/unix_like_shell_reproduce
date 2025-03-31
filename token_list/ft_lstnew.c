
#include "tokenlist.h"

t_list	*ft_lstnew(void *input)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->input = (char *)input;
	return (new_node);
}
