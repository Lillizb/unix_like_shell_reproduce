
#include "../minishell.h"

int	g_signal_code = 0;

void	signal_handle_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_signal_code = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	cleanup_and_exit(t_list **list, int status_code)
{
	if (list && *list)
		ft_lstclear(list, free);
	rl_clear_history ();
	exit(status_code);
}
