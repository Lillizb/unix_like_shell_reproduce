
#include "../minishell.h"

void	skip_content_in_dquotes(t_list **token_list, int *i, int *in_dquote)
{
	if ((*token_list)->content[*i] == D_QUOTE)
	{
		(*i)++;
		while ((*token_list)->content[*i]
			&& (*token_list)->content[*i] != D_QUOTE)
			(*i)++;
		(*i)++;
		*in_dquote = !(*in_dquote);
	}
}

void	skip_content_in_squotes(t_list **token_list, int *i, int *in_squote)
{
	if ((*token_list)->content[*i] == S_QUOTE)
	{
		(*i)++;
		while ((*token_list)->content[*i]
			&& (*token_list)->content[*i] != S_QUOTE)
			(*i)++;
		(*i)++;
		*in_squote = !(*in_squote);
	}
}

void	init_lexer_tkn(t_list *new_token, int t_len, int i)
{
	new_token->len = t_len;
	new_token->type = 0;
	new_token->index = i;
	new_token->n_flag = 0;
	new_token->cmd_index = -1;
	new_token->is_builtin = 0;
	new_token->content = NULL;
	new_token->result = NULL;
	new_token->tkn_array = NULL;
	new_token->env_array = NULL;
	new_token->filename = NULL;
	new_token->prev = NULL;
	new_token->next = NULL;
	malloc_for_content(new_token);
}

void	handle_dquote_content(t_list *new_token, t_list **token_list, 
				int t_len, int new_len)
{
	ft_strlcpy(new_token->content, "\"", new_len + 1);
	ft_strlcat(new_token->content, (*token_list)->content + t_len, new_len + 1);
	ft_strlcat(new_token->content, "\"", new_len + 1);
}

int	check_empty_string(t_list **token_list, char *input, int *start)
{
	t_list	*tmp;

	tmp = *token_list;
	if ((input[*start] == S_QUOTE && input[*start + 1] == S_QUOTE)
		|| (input[*start] == D_QUOTE && input[*start + 1] == D_QUOTE))
	{
		*start += 2;
		(*token_list)->content = NULL;
		*token_list = (*token_list)->next;
		ft_lstdelone(tmp, free);
		return (1);
	}
	return (0);
}
