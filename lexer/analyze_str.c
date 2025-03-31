
#include "../minishell.h"

void	return_code_routine(t_list **token_list, char *tmp, char *return_code)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while ((*token_list)->content[i])
	{
		if ((*token_list)->content[i] == '$'
			&& (*token_list)->content[i + 1] == '?')
		{
			k = 0;
			i += 2;
			while (return_code[k])
				tmp[j++] = return_code[k++];
		}
		else
			tmp[j++] = (*token_list)->content[i++];
	}
	tmp[j] = '\0';
}

void	find_return_code(t_list **token_list)
{
	char	*tmp;
	char	*return_code;

	return_code = ft_itoa((*token_list)->status_code);
	tmp = malloc(sizeof(char) * ((*token_list)->len - 2)
			+ ft_strlen(return_code) + 1);
	if (!tmp)
	{
		(*token_list)->status_code = ERROR_MALLOC;
		return ;
	}
	return_code_routine(token_list, tmp, return_code);
	free((*token_list)->content);
	free(return_code);
	(*token_list)->content = tmp;
	(*token_list)->len = ft_strlen((*token_list)->content);
}
