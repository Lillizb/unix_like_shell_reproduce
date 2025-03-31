
#include "../minishell.h"

void	ft_result_not_null(t_list **token_list, t_list **head,
		char *env_value, size_t *total_len)
{
	char	*new_result;

	new_result = (char *)malloc(sizeof(char) * ((*total_len) + 1));
	if (!new_result)
	{
		(*token_list)->status_code = ERROR_MALLOC;
		return ;
	}
	ft_strlcpy(new_result, (*head)->result, *total_len);
	if ((*token_list)->prev->no_space == 0)
		ft_strlcat(new_result, " ", *total_len + 1);
	if (env_value == NULL)
		ft_strlcat(new_result, (*token_list)->content, *total_len + 1);
	else
		ft_strlcat(new_result, env_value, *total_len + 1);
	free((*head)->result);
	(*head)->result = new_result;
}

void	ft_add_to_result_echo(t_list **token_list, char *env_value,
		size_t *total_len)
{
	t_list	*head;

	head = *token_list;
	while (head->prev && head->prev->type != PIPE && head->prev->type != END)
		head = head->prev;
	if (head->result == NULL)
	{
		head->result = (char *)malloc(sizeof(char) * (*total_len + 1));
		if (!head->result)
		{
			(*token_list)->status_code = ERROR_MALLOC;
			return ;
		}
		if (env_value == NULL)
			ft_strlcpy(head->result, (*token_list)->content, *total_len + 1);
		else
			ft_strlcpy(head->result, env_value, *total_len + 1);
	}
	else
	{
		if ((*token_list)->prev->no_space == 0)
			(*total_len) += 1;
		ft_result_not_null(token_list, &head, env_value, total_len);
	}
}

int	ft_total_len(t_list *token_list, char *env_value)
{
	int	counter;

	counter = 0;
	if (env_value)
		counter = ft_strlen(env_value);
	else if (token_list)
		counter = token_list->len;
	return (counter);
}
