

#include "../minishell.h"

char	*allocate_redir_tmp(t_list **token_list, int redir_len, int in_dquote)
{
	char	*tmp;

	if (in_dquote == 1)
		tmp = malloc(sizeof(char) * (redir_len + 2));
	else
		tmp = malloc(sizeof(char) * (redir_len + 1));
	if (!tmp)
	{
		ft_lstfirst((*token_list))->status_code = -1;
		return (NULL);
	}
	return (tmp);
}

void	copy_redir_content(t_list **token_list, int redir_len, char *tmp, int j)
{
	while (j < redir_len)
	{
		if ((*token_list)->content[j] == WHITESPACE)
			j++;
		else
		{
			tmp[j] = (*token_list)->content[j];
			j++;
		}
	}
}

void	is_whitespace(int *j, t_list **token_list)
{
	if ((*token_list)->content[*j] == WHITESPACE)
		(*j)++;
}

void	extract_redir(t_list **token_list, int j, int *in_dquote)
{
	int		redir_len;
	char	*tmp;

	redir_len = 0;
	while ((*token_list)->content[redir_len] == '>'
		|| (*token_list)->content[redir_len] == '<')
		redir_len++;
	tmp = allocate_redir_tmp(token_list, redir_len, *in_dquote);
	while (j < redir_len)
	{
		is_whitespace(&j, token_list);
		tmp[j] = (*token_list)->content[j];
		j++;
	}
	if (*in_dquote == 1)
		tmp[j++] = '"';
	tmp[j] = '\0';
	if ((*token_list)->content[j] != WHITESPACE)
		(*token_list)->no_space = 1;
	if ((*token_list)->content[j])
		create_new_token(token_list, redir_len, in_dquote);
	free((*token_list)->content);
	(*token_list)->content = tmp;
	(*token_list)->len = ft_strlen((*token_list)->content);
}

void	detect_redir_in_str(t_list **token_list, int *in_squote, int *in_dquote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*token_list)->content[i])
	{
		if (handle_squote(token_list, &i, in_squote, in_dquote) == 1)
			continue ;
		if (handle_dquote(token_list, &i, in_dquote, in_squote) == 1)
			continue ;
		if (((*token_list)->content[i] == '>'
				|| (*token_list)->content[i] == '<'))
		{
			if (i > 1)
				split_before_value(token_list, i, j, in_dquote);
			else
				extract_redir(token_list, j, in_dquote);
			break ;
		}
		i++;
	}
}
