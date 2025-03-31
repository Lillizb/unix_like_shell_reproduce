
#include "../minishell.h"

t_list	*create_new_env_node(t_list *token_list, t_list *env_list,
	char *new_content)
{
	t_list	*new_node;
	int		index;

	new_node = ft_lstnew(NULL);
	if (!new_node)
	{
		free(new_content);
		token_list->status_code = ERROR_MALLOC;
		return (NULL);
	}
	env_list = ft_lstlast(env_list);
	index = env_list->index + 1;
	init_env_list(env_list, new_node, index, ft_strlen(new_content));
	if (new_content)
		free(new_node->content);
	new_node->content = new_content;
	return (new_node);
}

void	create_env_content(t_list *token_list, char **new_content,
	char *name, char *value)
{
	*new_content = (char *)malloc(sizeof(char)
			* (ft_strlen(name) + ft_strlen(value) + 1));
	if (!(*new_content))
	{
		token_list->status_code = ERROR_MALLOC;
		return ;
	}
	if (name)
		ft_strlcpy(*new_content, name, ft_strlen(name) + ft_strlen(value) + 1);
	if (value)
		ft_strlcat(*new_content, value, ft_strlen(name) + ft_strlen(value) + 1);
}

void	ft_addenv(t_list *token_list, t_list *env_list, char *value, char *name)
{
	char	*new_content;

	create_env_content(token_list, &new_content, name, value);
	if (!new_content)
		return ;
	create_new_env_node(token_list, env_list, new_content);
}
