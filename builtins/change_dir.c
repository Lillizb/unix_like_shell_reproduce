/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:00:45 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 18:46:20 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_list *head, t_list **env_list, char **dir_path)
{
	char	*cwd;

	cwd = NULL;
	while (ft_strncmp((*env_list)->content, "PWD=", 4) != 0)
		*env_list = (*env_list)->next;
	cwd = ft_strdup((*env_list)->content + 4);
	*env_list = ft_lstfirst(*env_list);
	while (ft_strncmp((*env_list)->content, "OLDPWD=", 7) != 0)
		*env_list = (*env_list)->next;
	if (*env_list)
		ft_setenv(head, *env_list, cwd, "OLDPWD=");
	*env_list = ft_lstfirst(*env_list);
	free(cwd);
	cwd = getcwd(NULL, 0);
	while (ft_strncmp((*env_list)->content, "PWD=", 4) != 0)
		*env_list = (*env_list)->next;
	if (*env_list)
		ft_setenv(head, *env_list, cwd, "PWD=");
	free(cwd);
	free(*dir_path);
	*env_list = ft_lstfirst(*env_list);
}

int	calculate_total_len(t_list *token_list)
{
	int	total_len;

	total_len = 0;
	while (token_list)
	{
		total_len += token_list->len + 1;
		token_list = token_list->next;
	}
	return (total_len);
}

char	*ft_join_args(t_list *token_list)
{
	t_list	*head;
	int		total_len;
	char	*joined_str;

	total_len = calculate_total_len(token_list);
	joined_str = (char *)malloc(sizeof(char) * (total_len));
	if (!joined_str)
	{
		token_list->status_code = ERROR_MALLOC;
		return (NULL);
	}
	joined_str[0] = '\0';
	head = token_list;
	while (head)
	{
		ft_strlcat(joined_str, head->content, total_len);
		if (head->next)
			ft_strlcat(joined_str, " ", total_len);
		head = head->next;
	}
	return (joined_str);
}

int	check_for_pwd(t_list *token_list)
{
	while (token_list)
	{
		if (ft_strcmp(token_list->content, "$PWD") == 0)
		{
			perror("is not a valid identifier ");
			ft_lstfirst(token_list)->status_code = ERROR_GENERAL;
			return (1);
		}
		if (ft_strcmp(token_list->content, "$OLDPWD") == 0)
		{
			perror("is not a valid identifier ");
			ft_lstfirst(token_list)->status_code = ERROR_GENERAL;
			return (1);
		}
		token_list = token_list->next;
	}
	return (0);
}

int	ft_cd(t_list *token_list, t_list *env_list)
{
	t_list	*head;
	char	*dir_path;

	dir_path = NULL;
	head = token_list;
	token_list->is_builtin = 1;
	if (token_list->next)
		token_list = token_list->next;
	if (check_for_pwd(token_list) == 1)
		return (1);
	dir_path = ft_join_args(token_list);
	if (!dir_path)
	{
		ft_lstfirst(token_list)->status_code = ERROR_MALLOC;
		perror("Memory allocation error");
	}
	if (chdir(dir_path) == -1)
	{
		ft_lstfirst(token_list)->status_code = ERROR_GENERAL;
		free(dir_path);
		return (1);
	}
	update_env(head, &env_list, &dir_path);
	return (0);
}
