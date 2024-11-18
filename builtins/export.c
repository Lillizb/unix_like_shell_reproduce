/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:00:59 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 18:46:32 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_split_for_varname(t_list *token_list)
{
	int		i;
	char	*varname;

	i = 0;
	varname = NULL;
	if (!token_list)
		return (NULL);
	while (token_list->content[i] && token_list->content[i] != '=')
		i++;
	if (i <= token_list->len)
		varname = (char *)malloc(sizeof(char) * i + 2);
	if (!varname)
	{
		token_list->status_code = ERROR_MALLOC;
		return (NULL);
	}
	ft_strlcpy(varname, token_list->content, i + 1);
	return (varname);
}

char	*ft_split_for_value(t_list *token_list)
{
	int		len;
	int		start;
	char	*value;

	len = ft_strlen(token_list->content);
	start = 0;
	value = NULL;
	if (!token_list)
		return (NULL);
	while (token_list->content[start] && token_list->content[start] != '=')
		start++;
	if (start < token_list->len)
		value = (char *)malloc(sizeof(char) * (len - start));
	if (!value)
	{
		token_list->status_code = ERROR_MALLOC;
		return (NULL);
	}
	ft_strlcpy(value, &token_list->content[start + 1], len - start);
	return (value);
}

void	ft_add_to_result_export(t_list *token_list, char *varname, char *value)
{
	int	varname_len;
	int	value_len;

	varname_len = ft_strlen(varname);
	value_len = ft_strlen(value);
	token_list->result = (char *)ft_calloc ((varname_len + value_len + 1),
			sizeof(char));
	if (token_list->result)
	{
		ft_strlcpy(token_list->result, varname, (varname_len + value_len + 2));
		ft_strlcat(token_list->result, value, (varname_len + value_len + 2));
	}
}

void	ft_export_routine(t_list *token_list, t_list **env_list,
						char *varname, char *value)
{
	t_list	*current;

	current = *env_list;
	while (current && ft_strncmp(current->content, varname, ft_strlen(varname)))
		current = current->next;
	if (current)
		ft_setenv(token_list, current, value, varname);
	else if (!current)
		ft_addenv(token_list, *env_list, value, varname);
	if (varname && value)
		ft_add_to_result_export(token_list, varname, value);
	free(varname);
	free(value);
}

int	ft_export_env(t_list *token_list, t_list **env_list)
{
	char	*varname;
	char	*value;

	varname = NULL;
	value = NULL;
	if (!token_list || !env_list || !*env_list)
		return (1);
	token_list->is_builtin = 1;
	if (!token_list->next)
	{
		ft_sort_export_list(*env_list);
		ft_print_export_list(*env_list);
		return (0);
	}
	if (token_list->next)
		token_list = token_list->next;
	token_list->len = ft_strlen(token_list->content);
	if (check_env_name(token_list) == 1)
		return (1);
	varname = ft_split_for_varname(token_list);
	value = ft_split_for_value(token_list);
	ft_export_routine(token_list, env_list, varname, value);
	return (0);
}
