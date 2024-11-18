/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_exec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:18:06 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 18:44:35 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**token_list_to_array_exec(t_list *token_list)
{
	int		i;
	int		count;
	t_list	*tmp;
	char	**args;

	i = 0;
	tmp = token_list;
	count = count_token_elements(tmp);
	args = malloc((count + 1) * sizeof(char *));
	if (check_args_helper(token_list, args) == 1)
		return (NULL);
	tmp = token_list;
	while (i < count)
	{
		if (tmp->type != TRUNC && tmp->type != APPEND
			&& tmp->type != INPUT && tmp->type != DOUBLE_INPUT
			&& tmp->type != PIPE)
			args[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	**env_list_to_array_exec(t_list *token_list, t_list *env_list)
{
	int		i;
	int		count;
	t_list	*tmp;
	char	**env;

	i = 0;
	tmp = env_list;
	count = count_env_elements(tmp);
	env = malloc((count + 1) * sizeof(char *));
	if (!env)
	{
		ft_lstfirst(token_list)->status_code = ERROR_MALLOC;
		return (NULL);
	}
	tmp = env_list;
	while (i < count)
	{
		env[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	env[count] = NULL;
	return (env);
}
