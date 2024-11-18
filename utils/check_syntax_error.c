/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:02:23 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 18:23:02 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax_errors(t_list *token_list)
{
	while (token_list)
	{
		if ((token_list->type == PIPE || token_list->type == END)
			&& (token_list->next == NULL || token_list->next->type
				== PIPE || token_list->next->type == END))
		{
			printf("Syntax error: near unexpected tokens '%s' \n",
				token_list->content);
			token_list->status_code = SYNTAX_ERROR;
			return (1);
		}
		if ((token_list->type == TRUNC || token_list->type == APPEND
				|| token_list->type == INPUT
				|| token_list->type == DOUBLE_INPUT)
			&& (!token_list->next || token_list->next->type != ARG))
		{
			printf("Syntax error: near unexpected tokens '%s' \n",
				token_list->content);
			return (1);
		}
		token_list = token_list->next;
	}
	return (0);
}
