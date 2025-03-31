#include "../minishell.h"

t_list	*cmd_is_build_in(t_list *token_list, t_list **env_list)
{
	t_list	*head;

	head = token_list;
	while (token_list && token_list->type != PIPE)
	{
		handle_builtin_command(token_list, env_list);
		while (token_list && token_list->type != PIPE
			&& token_list->type != END)
			token_list = token_list->next;
	}
	return (head);
}

void	handle_builtin_command(t_list *token_list, t_list **env_list)
{
	ft_remove_quotes(token_list);
	if (token_list->type == CMD)
	{
		if (ft_strcmp(token_list->content, "echo") == 0)
			ft_echo(token_list, *env_list);
		else if (ft_strcmp(token_list->content, "cd") == 0)
			ft_cd(token_list, *env_list);
		else if (ft_strcmp(token_list->content, "pwd") == 0)
			ft_pwd(token_list);
		else if (ft_strcmp(token_list->content, "export") == 0)
			ft_export_env(token_list, env_list);
		else if (ft_strcmp(token_list->content, "unset") == 0)
			ft_unset_env(token_list, env_list);
		else if (ft_strcmp(token_list->content, "env") == 0)
			ft_allenv(token_list, env_list);
	}
}
