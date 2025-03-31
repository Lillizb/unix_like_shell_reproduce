
#include "../minishell.h"

void	ft_unset_env(t_list *token_list, t_list **env_list)
{
	t_list	*current;
	t_list	*prev;

	current = *env_list;
	prev = NULL;
	prepare_token_for_unset(&token_list);
	while (current)
	{
		if (ft_strncmp(current->content, token_list->content,
				token_list->len) == 0
			&& current->content[token_list->len] == '=')
		{
			if (prev == NULL)
				*env_list = current->next;
			else
				prev->next = current->next;
			ft_lstdelone(current, free);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	prepare_token_for_unset(t_list **token_list)
{
	(*token_list)->is_builtin = 1;
	if ((*token_list)->next)
		*token_list = (*token_list)->next;
	(*token_list)->len = ft_strlen((*token_list)->content);
}
