
#include "../minishell.h"

t_list	*init_env_list(t_list *env_list, t_list *new_node, int i, int j)
{
	new_node->len = j;
	new_node->type = 0;
	new_node->index = i;
	new_node->n_flag = 0;
	new_node->cmd_index = -1;
	new_node->is_builtin = 0;
	new_node->no_space = 0;
	new_node->content = NULL;
	new_node->result = NULL;
	new_node->tkn_array = NULL;
	new_node->env_array = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	malloc_for_content(new_node);
	ft_lstadd_back(&env_list, new_node);
	return (env_list);
}

t_list	*create_env_list(char **envp, char *input)
{
	t_list	*env_list;
	t_list	*new_node;
	int		i;
	int		len;

	i = 0;
	len = 0;
	new_node = NULL;
	env_list = NULL;
	while (envp[i])
	{
		len = ft_strlen(envp[i]);
		new_node = ft_lstnew(input);
		if (!new_node)
		{
			ft_lstclear(&env_list, free);
			return (NULL);
		}
		env_list = init_env_list(env_list, new_node, i, len);
		ft_strlcpy(new_node->content, envp[i], new_node->len);
		i++;
	}
	return (ft_lstfirst(env_list));
}
