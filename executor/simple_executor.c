/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:43:22 by ygao              #+#    #+#             */
/*   Updated: 2024/10/18 12:20:41 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_simple_result(t_list *token_list)
{
	if (token_list->result != NULL)
	{
		if (token_list->n_flag == 0)
			printf("%s\n", token_list->result);
		else if (token_list->n_flag == 1)
			printf("%s", token_list->result);
		else if (!token_list->n_flag && token_list->is_builtin == 1)
			printf("\n");
		ft_lstfirst(token_list)->status_code = 0;
	}
}

int	simple_executor(t_list *token_list, t_list **env_list)
{
	t_list	*head;

	head = token_list;
	if (check_for_heredoc(token_list))
		handle_heredoc(&token_list);
	token_list = head;
	if (handle_redir(&token_list) == 1)
		return (1);
	token_list = head;
	cmd_is_build_in(token_list, env_list);
	if (token_list->is_builtin == 0)
		token_list->status_code = cmd_is_exec(token_list, *env_list);
	print_simple_result(token_list);
	return (0);
}
