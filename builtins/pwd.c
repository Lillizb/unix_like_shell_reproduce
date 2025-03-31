
#include "../minishell.h"

void	ft_pwd(t_list *token_list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	token_list->is_builtin = 1;
	if (cwd)
		token_list->result = ft_strdup(cwd);
	free (cwd);
	cwd = NULL;
}
