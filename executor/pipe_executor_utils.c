/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:51:52 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 18:44:32 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipes(t_list *token_list, int **fd, int n_of_pipes)
{
	int	i;

	i = 0;
	while (i < n_of_pipes)
	{
		if (pipe(fd[i]) == -1)
		{
			token_list->status_code = ERROR_PIPE;
			return ;
		}
		i++;
	}
}

void	dup2_for_child(int **fd, int n_of_pipes, int i)
{
	int	j;

	j = 0;
	if (i > 0)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
	if (i < n_of_pipes)
	{
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][1]);
		close(fd[i][0]);
	}
	while (j < n_of_pipes)
	{
		if (j != i && j != (i - 1))
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		j++;
	}
}

t_list	*find_next_cmd(t_list **cmd_head)
{
	while ((*cmd_head) && (*cmd_head)->next && (*cmd_head)->type != PIPE)
		(*cmd_head) = (*cmd_head)->next;
	if ((*cmd_head)->next)
		(*cmd_head) = (*cmd_head)->next;
	if ((*cmd_head)->type != CMD)
		ft_lstfirst((*cmd_head));
	return (*cmd_head);
}

t_list	*find_last_cmd(t_list *token_list)
{
	while (token_list->next)
		token_list = token_list->next;
	if (token_list->type != CMD)
		token_list = ft_lstfirst(token_list);
	return (token_list);
}

void	print_pipe_result(t_list *cmd_head)
{
	if (cmd_head->result != NULL)
	{
		if (cmd_head->n_flag == 0)
			printf("%s\n", cmd_head->result);
		else if (cmd_head->n_flag == 1)
			printf("%s", cmd_head->result);
		else if (cmd_head->n_flag == 0 && cmd_head->is_builtin == 1)
			printf("\n");
		cmd_head->status_code = 0;
	}
}
