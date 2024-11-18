/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfirst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:37:35 by cwick             #+#    #+#             */
/*   Updated: 2024/09/20 12:16:48 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstfirst(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->prev != NULL && lst->prev->type != PIPE)
		lst = lst->prev;
	return (lst);
}
