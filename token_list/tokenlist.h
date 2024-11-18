/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:44:51 by ygao              #+#    #+#             */
/*   Updated: 2024/09/25 20:03:05 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENLIST_H
# define TOKENLIST_H

# include <stdlib.h>

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	int				index;
	int				cmd_index;
	int				type;
	int				len;
	int				n_flag;
	int				is_builtin;
	int				no_space;
	int				status_code;
	char			*input;
	char			*content;
	char			*result;
	char			*filename;
	char			**env_array;
	char			**tkn_array;
}	t_list;

// Create list and nodes
t_list	*ft_lstnew(void *input);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstfirst(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void*));

#endif
