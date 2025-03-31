
#include "../minishell.h"

void	env_list_to_array_env(t_list *token_list, t_list **env_list)
{
	int		len;
	t_list	*tmp;

	len = 0;
	tmp = *env_list;
	while (tmp)
	{
		len += tmp->len + 1;
		tmp = tmp->next;
	}
	token_list->result = malloc(sizeof(char) * (len + 1));
	if (!token_list->result)
	{
		token_list->status_code = ERROR_MALLOC;
		return ;
	}
	token_list->result[0] = '\0';
	tmp = *env_list;
	while (tmp)
	{
		ft_strlcat(token_list->result, tmp->content, len);
		if (tmp->next)
			ft_strlcat(token_list->result, "\n", len);
		tmp = tmp->next;
	}
}

t_list	*ft_allenv(t_list *token_list, t_list **env_list)
{
	token_list->is_builtin = 1;
	if (token_list->next && (token_list->next->type != PIPE
			&& token_list->next->type != TRUNC
			&& token_list->next->type != APPEND))
	{
		token_list->status_code = ERROR_GENERAL;
		printf("invalid Input: %s\n", token_list->input);
	}
	else
		env_list_to_array_env(token_list, env_list);
	return (*env_list);
}

char	*ft_getenv(t_list *env_list, char *var)
{
	int		i;
	t_list	*head;

	i = 0;
	head = env_list;
	while (env_list)
	{
		if (ft_strncmp(env_list->content, var, ft_strlen(var)) == 0
			&& env_list->content[ft_strlen(var)] == '=')
		{
			while (env_list->content[i] != '=')
				i++;
			return (ft_strdup(env_list->content + i + 1));
		}
		env_list = env_list->next;
	}
	env_list = head;
	return (NULL);
}

void	ft_setenv(t_list *token_list, t_list *env_node, char *value, char *name)
{
	char	*new_content;

	if (!env_node)
		return ;
	new_content = (char *)malloc(sizeof(char)
			* (ft_strlen(name) + ft_strlen(value) + 1));
	if (!new_content)
	{
		token_list->status_code = ERROR_MALLOC;
		return ;
	}
	ft_strlcpy(new_content, name, ft_strlen(name) + ft_strlen(value) + 1);
	ft_strlcat(new_content, value, ft_strlen(name) + ft_strlen(value) + 1);
	free(env_node->content);
	env_node->content = new_content;
}
