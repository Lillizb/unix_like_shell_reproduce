
#include "minishell.h"

void	save_status_code(t_list *token_list, int *status_code)
{
	t_list	*head;

	head = token_list;
	if (g_signal_code != 0)
	{
		*status_code = g_signal_code;
		g_signal_code = 0;
	}
	else if (token_list)
		*status_code = head->status_code;
}

void	free_split_input(char **split_input)
{
	int	i;

	i = 0;
	while (split_input[i])
	{
		free(split_input[i]);
		i++;
	}
	free(split_input);
}

int	check_input(char *input, t_list **env_list, int *status_code)
{
	char	**split_input;

	if (check_quotes(input))
	{
		*status_code = ERROR_GENERAL;
		free(input);
		return (1);
	}
	split_input = ft_split(input, ' ');
	if (split_input[0] != NULL && ft_strcmp(split_input[0], "exit") == 0)
		handle_exit(split_input, env_list, input);
	free_split_input(split_input);
	return (0);
}

void	setup_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handle_ctrlc);
}

// void	check_signal_code(int *status_code)
// {
// 	if (g_signal_code != 0)
// 	{
// 		*status_code = g_signal_code;
// 		g_signal_code = 0;
// 	}
// }
