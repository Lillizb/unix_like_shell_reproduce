/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_redir_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:07:04 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 17:08:02 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"	

int	handle_dquote(t_list **token_list, int *i, int *in_dquote, int *in_squote)
{
	if ((*token_list)->content[*i] == D_QUOTE && *in_squote == 0)
	{
		*in_dquote = !(*in_dquote);
		skip_content_in_dquotes(token_list, i, in_dquote);
		return (1);
	}
	return (0);
}

int	handle_squote(t_list **token_list, int *i, int *in_squote, int *in_dquote)
{
	if ((*token_list)->content[*i] == S_QUOTE && *in_dquote == 0)
	{
		*in_squote = !(*in_squote);
		skip_content_in_squotes(token_list, i, in_squote);
		return (1);
	}
	return (0);
}

void	handle_quotes_env(t_list **token_list, int *i, 
			int *in_squote, int *in_dquote)
{
	if ((*token_list)->content[*i] == S_QUOTE && (*in_dquote) == 0)
		skip_content_in_squotes(token_list, i, in_squote);
	else if ((*token_list)->content[*i] == D_QUOTE && (*in_squote) == 0)
	{
		(*in_dquote) = !(*in_dquote);
		(*i)++;
	}
}
