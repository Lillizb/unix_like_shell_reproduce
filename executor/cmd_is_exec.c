
#include "../minishell.h"

int	prepare_token_and_env_arrays(t_list *token_list, t_list **env_list);

void	child_process(pid_t pid, t_list *token_list,
			char **path_list, char **env)
{
	if (pid == 0)
	{
		while (path_list && *path_list)
		{
			execve(*path_list, token_list->tkn_array, env);
			path_list++;
		}
		perror("Command not found ");
		exit(ERROR_EXEC);
	}
}

int	create_run_process(t_list *token_list, char **org_path_list, char **env)
{
	pid_t	pid;
	int		last_status;
	int		status;
	char	**path_list;

	last_status = 0;
	path_list = org_path_list;
	pid = fork();
	child_process(pid, token_list, path_list, env);
	if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			token_list->status_code = ERROR_WAITPID;
			return (ERROR_WAITPID);
		}
		else if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	else
		last_status = ERROR_FORK;
	free_token_array(&token_list);
	free_env_array(&token_list);
	ft_lstfirst(token_list)->status_code = last_status;
	return (last_status);
}

void	add_cmd_to_path(t_list *token_list, char ***path_list)
{
	int		i;
	int		len;
	char	*new_path;

	i = 0;
	while ((*path_list)[i])
	{
		ft_remove_quotes(token_list);
		remove_colon(*path_list, i);
		len = ft_strlen((*path_list)[i]) + 1 + token_list->len + 1;
		new_path = (char *)malloc(len * sizeof(char));
		if (!new_path)
		{
			token_list->status_code = ERROR_MALLOC;
			return ;
		}
		ft_strlcpy(new_path, (*path_list)[i], len);
		ft_strlcat(new_path, "/", len);
		ft_strlcat(new_path, token_list->content, len);
		free((*path_list)[i]);
		(*path_list)[i] = new_path;
		i++;
	}
}

void	get_env_path(t_list *token_list, t_list *env_list, char ***path_list)
{
	char	*env_path;

	env_path = ft_getenv(env_list, "PATH");
	if (!env_path)
	{
		token_list->status_code = ERROR_MALLOC;
		return ;
	}
	*path_list = ft_split(env_path, ':');
	if (!*path_list)
	{
		token_list->status_code = ERROR_MALLOC;
		return ;
	}
	free(env_path);
	add_cmd_to_path(token_list, path_list);
}

int	cmd_is_exec(t_list *token_list, t_list *env_list)
{
	char	**path_list;

	path_list = NULL;
	ft_remove_quotes(token_list);
	if (is_absolute_path(token_list, env_list))
		return (0);
	get_env_path(token_list, env_list, &path_list);
	if (!path_list)
	{
		token_list->status_code = ERROR_CMD_PTH_NOT_FOUND;
		perror("No ENV Value: PATH");
		return (ERROR_CMD_PTH_NOT_FOUND);
	}
	if (prepare_token_and_env_arrays(token_list, &env_list) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	create_run_process(token_list, path_list, token_list->env_array);
	free_path_list(path_list);
	return (token_list->status_code);
}
