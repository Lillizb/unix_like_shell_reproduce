/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:58:45 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 16:18:27 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*allocate_pipe_tmp(t_list **token_list, int *in_dquote)
{
	char	*tmp;

	if (*in_dquote == 1)
		tmp = malloc(sizeof(char) * 3);
	else
		tmp = malloc(sizeof(char) * 2);
	if (!tmp)
	{
		ft_lstfirst((*token_list))->status_code = ERROR_MALLOC;
		return (NULL);
	}
	return (tmp);
}

void	extract_pipe(t_list **token_list, int j, int *in_dquote)
{
	char	*tmp;

	tmp = allocate_pipe_tmp(token_list, in_dquote);
	tmp[j] = (*token_list)->content[j];
	j++;
	if (*in_dquote == 1)
	{
		tmp[j] = '"';
		j++;
	}
	tmp[j] = '\0';
	if ((*token_list)->content[j] != WHITESPACE 
		&& (*token_list)->content[j] != '\0')
		(*token_list)->no_space = 1;
	if ((*token_list)->content[j])
		create_new_token(token_list, 1, in_dquote);
	if (tmp)
	{
		free((*token_list)->content);
		(*token_list)->content = tmp;
	}
	(*token_list)->content = tmp;
	(*token_list)->len = ft_strlen((*token_list)->content);
}

void	detect_pipe_in_str(t_list **token_list, int *in_squote, int *in_dquote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((*token_list)->content[0] == '|' && (*token_list)->content[1] == '\0')
		return ;
	while ((*token_list)->content[i])
	{
		if (handle_squote(token_list, &i, in_squote, in_dquote) == 1)
			continue ;
		if (handle_dquote(token_list, &i, in_dquote, in_squote) == 1)
			continue ;
		if ((*token_list)->content[i] == '|')
		{
			if (i > 1)
				split_before_value(token_list, i, j, in_dquote);
			else
				extract_pipe(token_list, j, in_dquote);
			break ;
		}
		i++;
	}
}
