
#include "../minishell.h"

int	prepare_for_execution(t_list *token_list, pid_t **pid,
	int ***fd, int n_of_pipes)
{
	malloc_for_fd(token_list, fd, n_of_pipes);
	malloc_for_pid(token_list, *fd, pid, n_of_pipes);
	if (check_for_heredoc(token_list))
		handle_heredoc(&token_list);
	token_list = ft_lstfirst(token_list);
	create_pipes(token_list, *fd, n_of_pipes);
	return (0);
}

t_list	*jump_to_first_node(t_list **token_list)
{
	while ((*token_list)->prev)
		(*token_list) = (*token_list)->prev;
	return ((*token_list));
}
