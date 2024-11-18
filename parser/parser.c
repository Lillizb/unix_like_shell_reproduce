/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:39:32 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 14:40:43 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	restore_stdin_stdout(t_list *token_list,
			int *saved_stdin, int *saved_stdout)
{
	if (dup2(*saved_stdin, STDIN_FILENO) == -1)
	{
		token_list->status_code = ERROR_DUP2;
		perror("Error restoring STDIN");
	}
	if (dup2(*saved_stdout, STDOUT_FILENO) == -1)
	{
		token_list->status_code = ERROR_DUP2;
		perror("Error restoring STDOUT");
	}
}

int	count_pipes_set_cmd_index(t_list *token_list)
{
	int	cmd_index;
	int	counter_pipes;

	cmd_index = 0;
	counter_pipes = 0;
	while (token_list)
	{
		if (token_list->type == PIPE)
			counter_pipes++;
		else if (token_list->type == CMD)
		{
			token_list->cmd_index = cmd_index;
			cmd_index++;
		}
		token_list = token_list->next;
	}
	return (counter_pipes);
}

t_list	*ft_parser(t_list *token_list, t_list **env_list)
{
	int	n_pipes;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	n_pipes = count_pipes_set_cmd_index(token_list);
	if (n_pipes == 0)
		simple_executor(token_list, env_list);
	else if (n_pipes > 0)
		pipe_executor(token_list, env_list, n_pipes);
	restore_stdin_stdout(token_list, &saved_stdin, &saved_stdout);
	close(saved_stdin);
	close(saved_stdout);
	return (token_list);
}
