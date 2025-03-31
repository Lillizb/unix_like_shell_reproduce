
#include "../minishell.h"

void	malloc_for_pid(t_list *token_list, int **fd, pid_t **pid,
		int n_of_pipes)
{
	int	i;

	i = 0;
	*pid = malloc(sizeof(pid_t) * (n_of_pipes + 1));
	if (!(*pid))
	{
		token_list->status_code = ERROR_MALLOC;
		while (i < n_of_pipes)
		{
			free(fd[i]);
			i++;
		}
		free(fd);
		return ;
	}
}

void	malloc_for_fd(t_list *token_list, int ***fd, int n_of_pipes)
{
	int	i;

	i = 0;
	*fd = malloc(sizeof(int *) * n_of_pipes);
	if (!(*fd))
	{
		token_list->status_code = ERROR_MALLOC;
		return ;
	}
	while (i < n_of_pipes)
	{
		(*fd)[i] = malloc(sizeof(int) * 2);
		if (!(*fd)[i])
		{
			token_list->status_code = ERROR_MALLOC;
			while (--i >= 0)
				free((*fd)[i]);
			free(*fd);
			return ;
		}
		i++;
	}
}

int	check_for_heredoc(t_list *token_list)
{
	while (token_list)
	{
		if (token_list->type == DOUBLE_INPUT)
			return (1);
		token_list = token_list->next;
	}
	return (0);
}
