/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:23:53 by ygao              #+#    #+#             */
/*   Updated: 2024/10/18 13:15:54 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_fd(int fd)
{
	if (fd == -1)
	{
		perror("missing");
		return (1);
	}
	return (0);
}

int	open_output_file(t_list **token)
{
	int	file;

	file = 0;
	if ((*token)->next && (*token)->next->content)
	{
		ft_remove_quotes((*token)->next);
		if ((*token)->type == TRUNC)
			file = open((*token)->next->content,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if ((*token)->type == APPEND)
			file = open((*token)->next->content,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	if (check_fd(file) == 1)
	{
		ft_lstfirst((*token))->status_code = ERROR_GENERAL;
		return (-1);
	}
	return (file);
}

int	handle_output_redirection(t_list **token)
{
	int	file;

	file = open_output_file(token);
	if (file == -1)
		return (1);
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		ft_lstfirst(*token)->status_code = -1;
		close(file);
		return (1);
	}
	if (file > 0)
		close(file);
	return (0);
}

int	handle_type(t_list **token, int *file)
{
	if ((*token)->type == INPUT)
	{
		if ((*token)->next && (*token)->next->content)
		{
			ft_remove_quotes((*token)->next);
			*file = open((*token)->next->content, O_RDONLY);
		}
		if (check_fd(*file) == 1)
		{
			ft_lstfirst((*token))->status_code = ERROR_GENERAL;
			return (1);
		}
		if (dup2(*file, STDIN_FILENO) == -1)
			ft_lstfirst((*token))->status_code = -1;
	}
	else if ((*token)->type == TRUNC || (*token)->type == APPEND)
	{
		if (handle_output_redirection(token) == 1)
			return (1);
	}
	if (*file > 0)
		close(*file);
	return (0);
}

int	handle_redir(t_list **token_list)
{
	int		file;
	t_list	*head;

	file = 0;
	head = *token_list;
	while (*token_list && (*token_list)->type != PIPE
		&& (*token_list)->type != END)
	{
		if ((*token_list)->type == TRUNC || (*token_list)->type == APPEND
			|| (*token_list)->type == INPUT)
		{
			if (check_next_token (token_list) == 1)
			{
				perror ("syntax error near unexpected token '>'");
				return (1);
			}
			if (handle_type(token_list, &file) == 1)
			{
				(head)->status_code = 1;
				return (1);
			}
		}
		*token_list = (*token_list)->next;
	}
	return (0);
}
