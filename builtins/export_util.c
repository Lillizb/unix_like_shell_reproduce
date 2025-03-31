
#include "../minishell.h"

int	first_pos_num_or_equal(t_list *token_list)
{
	if ((token_list->content[0] >= '0' && token_list->content[0] <= '9')
		|| token_list->content[0] == '=')
	{
		perror("is not a valid identifier ");
		ft_lstfirst(token_list)->status_code = ERROR_GENERAL;
		return (1);
	}
	return (0);
}

int	check_env_name(t_list *token_list)
{
	int	i;

	i = 0;
	if (first_pos_num_or_equal(token_list) == 1)
		return (1);
	while (token_list->content[i] && token_list->content[i] != '=')
	{
		if (token_list->content[i] == '_'
			|| (token_list->content[i] >= 'A'
				&& token_list->content[i] <= 'Z')
			|| (token_list->content[i] >= 'a'
				&& token_list->content[i] <= 'z')
			|| (token_list->content[i] >= '0'
				&& token_list->content[i] <= '9'))
			i++;
		else
		{
			perror("is not a valid identifier ");
			ft_lstfirst(token_list)->status_code = ERROR_GENERAL;
			return (1);
		}
	}
	return (0);
}

void	ft_print_export_list(t_list *env_list)
{
	t_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		printf("declare -x %s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	ft_swap_content(t_list *a, t_list *b)
{
	char	*tmp_content;
	int		tmp_len;

	tmp_content = a->content;
	a->content = b->content;
	b->content = tmp_content;
	tmp_len = a->len;
	a->len = b->len;
	b->len = tmp_len;
}

void	ft_sort_export_list(t_list *env_list)
{
	t_list	*current;
	t_list	*next;
	int		sorted;

	if (!env_list)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = env_list;
		while (current->next)
		{
			next = current->next;
			if (ft_strcmp(current->content, next->content) > 0)
			{
				ft_swap_content(current, next);
				sorted = 0;
			}
			current = current->next;
		}
	}
}
