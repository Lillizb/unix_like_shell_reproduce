/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:15:29 by cwick             #+#    #+#             */
/*   Updated: 2024/10/18 13:30:05 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_next_token(t_list **token_list)
{
	if ((*token_list)->next->type == TRUNC 
		|| (*token_list)->next->type == APPEND
		|| (*token_list)->next->type == INPUT)
		return (1);
	return (0);
}
