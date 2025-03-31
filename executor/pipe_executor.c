
#include "../minishell.h"

void	free_fd_and_pid(int **fd, pid_t *pid, int n_of_pipes)
{
	int	i;

	i = 0;
	while (i < n_of_pipes)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	free(pid);
}

void	close_all_fds(int **fd, int n_of_pipes)
{
	int	i;

	i = 0;
	while (i < n_of_pipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	close_fd_and_waitpid(t_list *token_list, pid_t *pid,
	int **fd, int n_of_pipes)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	close_all_fds(fd, n_of_pipes);
	i = 0;
	while (i <= n_of_pipes)
	{
		if (waitpid(pid[i], &status, 0) == -1)
		{
			perror("waitpid failed");
			token_list->status_code = ERROR_WAITPID;
		}
		else if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	token_list->status_code = last_status;
	free_fd_and_pid(fd, pid, n_of_pipes);
}

int	child_process_pipe(t_list **env_list, t_list **cmd_head)
{
	t_list	*tmp;

	tmp = *cmd_head;
	if (handle_redir(cmd_head) == 1)
		exit(EXIT_FAILURE);
	*cmd_head = tmp;
	cmd_is_build_in(*cmd_head, env_list);
	if ((*cmd_head)->is_builtin == 1)
		print_pipe_result(*cmd_head);
	if ((*cmd_head)->is_builtin == 0)
	{
		(*cmd_head)->status_code = cmd_is_exec(*cmd_head, *env_list);
		exit((*cmd_head)->status_code);
	}
	exit(EXIT_SUCCESS);
}

void	pipe_executor(t_list *token_list, t_list **env_list, int n_of_pipes)
{
	int		i;
	int		**fd;
	pid_t	*pid;

	i = prepare_for_execution(token_list, &pid, &fd, n_of_pipes);
	while (i <= n_of_pipes)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			token_list->status_code = ERROR_FORK;
			free_fd_and_pid(fd, pid, n_of_pipes);
			return ;
		}
		else if (pid[i] == 0)
		{
			dup2_for_child(fd, n_of_pipes, i);
			if (child_process_pipe(env_list, &token_list) == 1)
				break ;
			exit(EXIT_SUCCESS);
		}
		find_next_cmd(&token_list);
		i++;
	}
	close_fd_and_waitpid(jump_to_first_node(&token_list), pid, fd, n_of_pipes);
}
