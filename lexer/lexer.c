#include "../minishell.h"

void	detect_in_str(t_list **token_list, int *in_squote, int *in_dquote)
{
	t_list	*head;

	head = (*token_list);
	while ((*token_list))
	{
		detect_redir_in_str(token_list, in_squote, in_dquote);
		(*token_list) = (*token_list)->next;
	}
	(*token_list) = head;
	while ((*token_list))
	{
		detect_env_in_str(token_list, in_squote, in_dquote);
		(*token_list) = (*token_list)->next;
	}
	(*token_list) = head;
	while ((*token_list))
	{
		detect_pipe_in_str(token_list, in_squote, in_dquote);
		if (ft_strcmp(ft_lstfirst(*token_list)->content, "echo") != 0)
			ft_remove_quotes(*token_list);
		define_type((*token_list));
		(*token_list) = (*token_list)->next;
	}
}

t_list	*create_new_token(t_list **token_list, int t_len, 
			int *in_dquote)
{
	t_list	*new_token;
	int		new_len;

	new_len = 0;
	if (t_len < (*token_list)->len)
		new_len = (*token_list)->len - t_len;
	else
		new_len = t_len;
	if (*in_dquote == 1)
		new_len++;
	new_token = ft_lstnew(NULL);
	init_lexer_tkn(new_token, new_len, (*token_list)->index + 1);
	if (*in_dquote == 1)
		handle_dquote_content(new_token, token_list, t_len, new_len);
	else
		ft_strlcpy(new_token->content, (*token_list)->content + t_len, new_len);
	new_token->next = (*token_list)->next;
	new_token->prev = (*token_list);
	(*token_list)->next = new_token;
	if (*in_dquote == 1)
		*in_dquote = !(*in_dquote);
	return (new_token);
}

t_list	*lexer(char *input, int n_of_token, t_list **env_list, int status_code)
{
	t_list	*head;
	t_list	*token_list;
	int		in_squote;
	int		in_dquote;

	head = NULL;
	token_list = NULL;
	in_squote = 0;
	in_dquote = 0;
	token_list = create_tkn_lst(token_list, input, n_of_token, status_code);
	if (!token_list)
		return (NULL);
	head = token_list;
	if (check_syntax_errors(head) == 1)
		return (NULL);
	token_list = split_string(token_list, input, n_of_token);
	detect_in_str(&token_list, &in_squote, &in_dquote);
	token_list = head;
	ft_parser(token_list, env_list);
	return (head);
}

t_list	*split_string(t_list *token_list, char *input, int n_of_token)
{
	int		i;
	int		start;
	t_list	*head;

	i = 0;
	start = 0;
	head = token_list;
	while (i < n_of_token)
	{
		if (token_list->prev && input[start] != WHITESPACE)
			token_list->no_space = 1;
		while (input[start] == WHITESPACE)
			start++;
		if (check_empty_string(&token_list, input, &start) == 0 && token_list)
		{
			ft_strlcpy(token_list->content, &input[start], token_list->len);
			start += token_list->len;
			token_list = token_list->next;
		}
		i++;
	}
	return (head);
}
