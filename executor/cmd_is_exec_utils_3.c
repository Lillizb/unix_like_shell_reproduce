/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_exec_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:20 by chris             #+#    #+#             */
/*   Updated: 2024/10/05 18:44:33 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_colon(char **path_list, int i)
{
	int	j;

	j = 0;
	while (path_list[i][j] != '\0')
	{
		if (path_list[i][j] == ':')
		{
			path_list[i][j] = '\0';
			break ;
		}
		j++;
	}
}

void	free_path_list(char **path_list)
{
	int	i;

	i = 0;
	if (path_list && *path_list)
	{
		while (path_list[i])
		{
			free(path_list[i]);
			i++;
		}
		free(path_list);
	}
}

int	check_args_helper(t_list *token, char **args)
{
	if (!args)
	{
		ft_lstfirst(token)->status_code = ERROR_MALLOC;
		return (1);
	}
	return (0);
}

int	count_token_elements(t_list *token_list)
{
	int	count;

	count = 0;
	while (token_list && token_list->type != TRUNC && token_list->type != APPEND
		&& token_list->type != INPUT && token_list->type != DOUBLE_INPUT
		&& token_list->type != PIPE)
	{
		count++;
		token_list = token_list->next;
	}
	return (count);
}

int	count_env_elements(t_list *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}
