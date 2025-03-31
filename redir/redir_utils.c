
#include "../minishell.h"

int	check_next_token(t_list **token_list)
{
	if ((*token_list)->next->type == TRUNC 
		|| (*token_list)->next->type == APPEND
		|| (*token_list)->next->type == INPUT)
		return (1);
	return (0);
}
