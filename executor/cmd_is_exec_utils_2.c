
#include "../minishell.h"

void	free_token_array(t_list **token_list)
{
	int		i;

	i = 0;
	if (!(*token_list) || !(*token_list)->env_array)
		return ;
	while ((*token_list)->tkn_array[i])
	{
		free((*token_list)->tkn_array[i]);
		i++;
	}
	free((*token_list)->tkn_array);
	(*token_list)->tkn_array = NULL;
}

void	free_env_array(t_list **token_list)
{
	int		i;

	i = 0;
	if (!(*token_list) || !(*token_list)->env_array)
		return ;
	while ((*token_list)->env_array[i])
	{
		free((*token_list)->env_array[i]);
		i++;
	}
	free((*token_list)->env_array);
	(*token_list)->env_array = NULL;
}

int	is_absolute_path(t_list *token_list, t_list *env_list)
{
	if (token_list->content[0] == '/')
	{
		token_list->tkn_array = token_list_to_array_exec(token_list);
		token_list->env_array = env_list_to_array_exec(token_list, env_list);
		if (!token_list->tkn_array || !token_list->env_array)
		{
			if (token_list->tkn_array)
				free_token_array(&token_list);
			if (token_list->env_array)
				free_env_array(&token_list);
			token_list->status_code = ERROR_MALLOC;
			return (ERROR_MALLOC);
		}
		create_run_process(token_list, &token_list->content,
			token_list->env_array);
		return (1);
	}
	return (0);
}

int	prepare_token_and_env_arrays(t_list *token_list, t_list **env_list)
{
	token_list->tkn_array = token_list_to_array_exec(token_list);
	token_list->env_array = env_list_to_array_exec(token_list, *env_list);
	if (!token_list->tkn_array || !token_list->env_array)
	{
		if (token_list->tkn_array)
			free_token_array(&token_list);
		if (token_list->env_array)
			free_env_array(&token_list);
		token_list->status_code = ERROR_MALLOC;
		return (ERROR_MALLOC);
	}
	return (0);
}
