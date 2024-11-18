/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:01:08 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 18:47:00 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_env(t_list *token_list, t_list **env_list)
{
	t_list	*current;
	t_list	*prev;

	current = *env_list;
	prev = NULL;
	prepare_token_for_unset(&token_list);
	while (current)
	{
		if (ft_strncmp(current->content, token_list->content,
				token_list->len) == 0
			&& current->content[token_list->len] == '=')
		{
			if (prev == NULL)
				*env_list = current->next;
			else
				prev->next = current->next;
			ft_lstdelone(current, free);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	prepare_token_for_unset(t_list **token_list)
{
	(*token_list)->is_builtin = 1;
	if ((*token_list)->next)
		*token_list = (*token_list)->next;
	(*token_list)->len = ft_strlen((*token_list)->content);
}
