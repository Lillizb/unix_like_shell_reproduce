
#include "../minishell.h"

int	is_env_variable(t_list *token_list)
{
	if ((token_list->content[0] == '$'
			&& token_list->content[1] != WHITESPACE
			&& token_list->content[1] != S_QUOTE
			&& token_list->content[1] != D_QUOTE
			&& token_list->content[1] != '?'
			&& token_list->content[1] != '\0'))
		return (1);
	else if ((ft_strncmp(token_list->content, "\"$", 2) == 0
			&& token_list->content[2] != WHITESPACE
			&& token_list->content[2] != S_QUOTE
			&& token_list->content[2] != D_QUOTE
			&& token_list->content[2] != '?'
			&& token_list->content[2] != '\0'))
		return (1);
	return (0);
}

int	ft_handle_env_variable(t_list *token_list,
	char *env_value, size_t *total_len)
{
	if (env_value)
	{
		ft_add_to_result_echo(&token_list, env_value, total_len);
		free(env_value);
	}
	else if (token_list->next || token_list->prev->prev)
	{
		free(token_list->content);
		token_list->content = NULL;
		token_list->status_code = ERROR_GENERAL;
		return (1);
	}
	return (0);
}

int	ft_echo_routine(t_list *token_list, t_list *env_list,
			char *env_value, size_t *total_len)
{
	if (is_env_variable(token_list) == 1)
	{
		ft_remove_quotes(token_list);
		env_value = ft_getenv(env_list, token_list->content + 1);
		*total_len += ft_total_len(token_list, env_value);
		if (ft_handle_env_variable(token_list, env_value, total_len) == 1)
			return (1);
	}
	else if (token_list->type == TRUNC || token_list->type == APPEND
		|| token_list->type == INPUT || token_list->type == DOUBLE_INPUT)
		return (1);
	else
	{
		ft_remove_quotes(token_list);
		*total_len += ft_total_len(token_list, env_value);
		ft_add_to_result_echo(&token_list, env_value, total_len);
	}
	return (0);
}

void	ft_process_echo_tokens(t_list *token_list, t_list *env_list,
		size_t *total_len, char *env_value)
{
	while (token_list)
	{
		if (token_list->type == PIPE || token_list->type == END)
			break ;
		if (ft_strcmp(token_list->content, "-n") == 0 && token_list->index == 1)
			token_list->prev->n_flag = 1;
		else
		{
			if (ft_echo_routine(token_list, env_list, env_value, total_len))
			{
				if (token_list->type == TRUNC || token_list->type == APPEND
					|| token_list->type == INPUT
					|| token_list->type == DOUBLE_INPUT)
					token_list = token_list->next->next;
				else
					token_list = token_list->next;
				continue ;
			}
		}
		token_list = token_list->next;
	}
}

t_list	*ft_echo(t_list *token_list, t_list *env_list)
{
	size_t	total_len;
	char	*env_value;

	total_len = 0;
	env_value = NULL;
	token_list->is_builtin = 1;
	token_list = token_list->next;
	ft_process_echo_tokens(token_list, env_list, &total_len, env_value);
	return (ft_lstfirst(token_list));
}
