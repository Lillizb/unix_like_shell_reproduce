/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:01:04 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 18:46:25 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_list *token_list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	token_list->is_builtin = 1;
	if (cwd)
		token_list->result = ft_strdup(cwd);
	free (cwd);
	cwd = NULL;
}
