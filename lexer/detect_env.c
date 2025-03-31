
#include "../minishell.h"

void	split_before_value(t_list **token_list, int i, int j, int *in_dquote)
{
	char	*tmp;

	tmp = allocate_redir_tmp(token_list, i, *in_dquote);
	while (j < i)
	{
		tmp[j] = (*token_list)->content[j];
		j++;
	}
	if ((*token_list)->content[j] != WHITESPACE)
		(*token_list)->no_space = 1;
	if (*in_dquote == 1)
	{
		tmp[j] = '"';
		j++;
	}
	tmp[j] = '\0';
	create_new_token(token_list, i, in_dquote);
	free((*token_list)->content);
	(*token_list)->content = tmp;
}

int	count_env_var_len(t_list *token_list, int *in_dquote)
{
	int	i;

	i = 1;
	if (*in_dquote == 1)
		i++;
	while ((token_list->content[i] >= 'A' && token_list->content[i] <= 'Z') 
		|| (token_list->content[i] >= 'a' && token_list->content[i] 
			<= 'z') || (token_list->content[i] >= '_'))
		i++;
	if (*in_dquote == 1 && token_list->content[i] == D_QUOTE)
	{
		i++;
		*in_dquote = !(*in_dquote);
	}
	return (i);
}

void	extract_env(t_list **token_list, int j, int *in_dquote)
{
	int		env_len;
	char	*tmp;

	env_len = count_env_var_len((*token_list), in_dquote);
	tmp = allocate_redir_tmp(token_list, env_len, *in_dquote);
	if (*in_dquote == 1 && (*token_list)->content[env_len] != D_QUOTE)
		tmp[j++] = '"';
	while (j < env_len)
	{
		is_whitespace(&j, token_list);
		tmp[j] = (*token_list)->content[j];
		j++;
	}
	if (*in_dquote == 1 && (*token_list)->content[env_len] != D_QUOTE)
		tmp[j++] = '"';
	tmp[j] = '\0';
	if ((*token_list)->content[env_len] != WHITESPACE 
		|| (*token_list)->content[env_len] == WHITESPACE)
		(*token_list)->no_space = 1;
	if ((*token_list)->content[env_len])
		create_new_token(token_list, env_len, in_dquote);
	free((*token_list)->content);
	(*token_list)->content = tmp;
}

void	detect_env_in_str(t_list **token_list, int *in_squote, int *in_dquote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*token_list)->content[i])
	{
		handle_quotes_env(token_list, &i, in_squote, in_dquote);
		if ((*token_list)->content[i] == '$'
			&& (*token_list)->content[i + 1] == '?' && (*in_squote) == 0)
			find_return_code(token_list);
		else if (is_env_variable_ii(*token_list, i) == 1)
		{
			if (i > 1)
				split_before_value(token_list, i, j, in_dquote);
			else if (i > 0)
				extract_env(token_list, j, in_dquote);
			break ;
		}
		i++;
	}
}

int	is_env_variable_ii(t_list *token_list, int i)
{
	if (token_list->content[i] == '$' && 
		((token_list->content[i + 1] == '_') || 
			((token_list->content[i + 1] >= 'A' 
					&& token_list->content[i + 1] <= 'Z') 
				|| (token_list->content[i + 1] >= 'a' 
					&& token_list->content[i + 1] <= 'z'))))
		return (1);
	return (0);
}
