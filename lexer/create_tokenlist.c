/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokenlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:53:08 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 16:08:48 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*malloc_for_content(t_list *new_node)
{
	new_node->content = (char *)malloc(sizeof(char) * (new_node->len + 1));
	if (!new_node->content)
	{
		ft_lstfirst(new_node)->status_code = ERROR_MALLOC;
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

t_list	*init_tkn(t_list *token_list, t_list *new_token, int t_len, int i)
{
	new_token->len = t_len;
	new_token->type = 0;
	new_token->index = i;
	new_token->n_flag = 0;
	new_token->cmd_index = -1;
	new_token->is_builtin = 0;
	new_token->no_space = 0;
	new_token->status_code = 0;
	new_token->content = NULL;
	new_token->result = NULL;
	new_token->tkn_array = NULL;
	new_token->env_array = NULL;
	new_token->filename = NULL;
	new_token->prev = NULL;
	new_token->next = NULL;
	malloc_for_content(new_token);
	ft_lstadd_back(&token_list, new_token);
	return (token_list);
}

t_list	*create_and_init_token(t_list *token_list, char **input,
			int i, int status_code)
{
	t_list	*new_token;
	int		t_len;
	int		j;

	j = 0;
	while ((*input)[j] == WHITESPACE)
		j++;
	(*input) += j;
	t_len = token_len((*input));
	new_token = ft_lstnew((*input));
	if (!new_token)
	{
		ft_lstclear(&token_list, free);
		return (NULL);
	}
	token_list = init_tkn(token_list, new_token, t_len, i);
	new_token->status_code = status_code;
	(*input) += t_len;
	return (new_token);
}

t_list	*create_tkn_lst(t_list *token_list, char *input, int n_of_token,
	int status_code)
{
	int		i;
	t_list	*head;
	t_list	*new_token;

	i = 0;
	head = NULL;
	new_token = NULL;
	while (i < n_of_token)
	{
		new_token = create_and_init_token(token_list, &input, i, status_code);
		if (!new_token)
			return (NULL);
		token_list = new_token;
		i++;
	}
	head = ft_lstfirst(token_list);
	return (head);
}
// t_list	*create_and_init_token(t_list *token_list, char *input, 
// 			int t_len, int i)
// {
// 	t_list	*new_token;

// 	new_token = ft_lstnew(input);
// 	if (!new_token)
// 	{
// 		ft_lstclear(&token_list, free);
// 		return (NULL);
// 	}
// 	token_list = init_tkn(token_list, new_token, t_len, i);
// 	token_list = new_token;
// 	return (token_list);
// }
// t_list	*create_tkn_lst(t_list *token_list, char *input, int n_of_token)
// {
// 	int		i;
// 	int		j;
// 	int		t_len;
// 	t_list	*head;
// 	t_list	*new_token;

// 	i = 0;
// 	j = 0;
// 	t_len = 0;
// 	head = NULL;
// 	new_token = NULL;
// 	while (i < n_of_token)
// 	{
// 		j = 0;
// 		while (input[j] == WHITESPACE)
// 			j++;
// 		input += j;
// 		t_len = token_len(input);
// 		new_token = ft_lstnew(input);
// 		if (!new_token)
// 		{
// 			ft_lstclear(&token_list, free);
// 			return (NULL);
// 		}
// 		token_list = init_tkn(token_list, new_token, t_len, i);
// 		token_list = new_token;
// 		input += t_len;
// 		i++;
// 	}
// 	head = ft_lstfirst(token_list);
// 	return (head);
// }
//---------------------------------------------------
// t_list	*create_tkn_lst(t_list *token_list, char *input, int n_of_token)
// {
// 	int		i;
// 	int		j;
// 	int		t_len;
// 	t_list	*new_token;

// 	i = 0;
// 	//j = 0;
// 	t_len = 0;
// 	new_token = NULL;
// 	while (i < n_of_token)
// 	{
// 		j = 0;
// 		skip_space(input, j);
// 		input += j;
// 		t_len = token_len(input);
// 		new_token = ft_lstnew(input);
// 		if (!new_token)
// 		{
// 			ft_lstclear(&token_list, free);
// 			return (NULL);
// 		}
// 		token_list = init_tkn(token_list, new_token, t_len, i);
// 		token_list = new_token;
// 		input += t_len;
// 		i++;
// 	}
// 	return (ft_lstfirst(token_list));
// }

// void	skip_space(char *input, int j)
// {
// 	while (input[j] == WHITESPACE)
// 		j++;
// }
//---------------------------------------------------
// t_list	*create_tkn_lst(t_list *token_list, char *input, int n_of_token)
// {
// 	int		i;
// 	int		j;
// 	int		t_len;
// 	t_list	*head;

// 	i = 0;
// 	head = NULL;
// 	while (i < n_of_token)
// 	{
// 		j = 0;
// 		t_len = 0;
// 		while (input[j] == WHITESPACE)
// 		{
// 			(j)++;
// 			// t_len++;
// 		}	
// 		t_len += token_len(input);
// 		token_list = create_and_init_token(token_list, input, t_len, i);
// 		if (!token_list)
// 			return (NULL);
// 		input += t_len;
// 		i++;
// 	}
// 	head = ft_lstfirst(token_list);
// 	return (head);
// }
