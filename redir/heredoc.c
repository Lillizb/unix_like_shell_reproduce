
#include "../minishell.h"

void	process_heredoc_input(int fd[2], t_list **token)
{
	char	*line;

	while ((*token)->type != DOUBLE_INPUT)
		(*token) = (*token)->next;
	while (1)
	{
		ft_putstr_fd("> ", STDERR);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		if ((ft_strncmp(line, (*token)->next->content,
					ft_strlen((*token)->next->content)) == 0)
			&& line[ft_strlen((*token)->next->content)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_lstfirst((*token))->status_code = -1;
	close(fd[0]);
}

void	handle_heredoc(t_list **token)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_lstfirst((*token))->status_code = -1;
		return ;
	}
	process_heredoc_input(fd, token);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_lstfirst((*token))->status_code = -1;
	close(fd[0]);
}
