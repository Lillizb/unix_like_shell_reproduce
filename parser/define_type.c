/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:24:42 by ygao              #+#    #+#             */
/*   Updated: 2024/09/23 17:24:43 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	define_type(t_list *token)
{
	int	quote_flag;

	quote_flag = 0;
	if (ft_strchr(token->content, '"') || ft_strchr(token->content, '\''))
		quote_flag = 1;
	if (ft_strcmp(token->content, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->content, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->content, "<<") == 0)
		token->type = DOUBLE_INPUT;
	else if (ft_strcmp(token->content, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->content, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->content, ";") == 0)
		token->type = END;
	else if (ft_strncmp(token->content, "-", 1) == 0 && !quote_flag)
		token->type = FLAG;
	else if (token->prev == NULL || token->prev->type == PIPE
		|| token->prev->type == END)
		token->type = CMD;
	else
		token->type = ARG;
}
