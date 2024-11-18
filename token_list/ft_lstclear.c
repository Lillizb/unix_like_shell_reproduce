/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 08:11:11 by cwick             #+#    #+#             */
/*   Updated: 2024/09/25 14:16:40 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenlist.h"

void	ft_arrayclear(char ***array)
{
	int	i;

	i = 0;
	if (!array || !(*array))
		return ;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		(*lst)->input = NULL;
		if ((*lst)->content != NULL)
		{
			del((*lst)->content);
			(*lst)->content = NULL;
		}
		if ((*lst)->result != NULL)
		{
			del((*lst)->result);
			(*lst)->result = NULL;
		}
		if ((*lst)->tkn_array != NULL)
			ft_arrayclear(&(*lst)->tkn_array);
		if ((*lst)->env_array != NULL)
			ft_arrayclear(&(*lst)->env_array);
		free(*lst);
		(*lst) = tmp;
	}
}
