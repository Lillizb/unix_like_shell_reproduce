
#include "../minishell.h"

void	process_quotes(t_list *token_list, char **temp,
	int *in_squote, int *in_dquote)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (token_list->content[i])
	{
		if (token_list->content[i] == D_QUOTE && *in_squote == 0)
			*in_dquote = !(*in_dquote);
		else if (token_list->content[i] == S_QUOTE && *in_dquote == 0)
			*in_squote = !(*in_squote);
		else if (token_list->content[i])
		{
			(*temp)[j] = token_list->content[i];
			j++;
		}
		i++;
	}
	(*temp)[j] = '\0';
}

int	count_quotes(t_list *token, int *in_squote, int *in_dquote)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (token->content[i])
	{
		if (token->content[i] == D_QUOTE && *in_squote == 0)
		{
			*in_dquote = !(*in_dquote);
			counter++;
		}
		else if (token->content[i] == S_QUOTE && *in_dquote == 0)
		{
			*in_squote = !(*in_squote);
			counter ++;
		}
		i++;
	}
	return (counter);
}

void	ft_remove_quotes(t_list *token)
{
	int		in_squote;
	int		in_dquote;
	int		n_of_quotes;
	char	*temp;

	in_squote = 0;
	in_dquote = 0;
	n_of_quotes = 0;
	temp = NULL;
	n_of_quotes = count_quotes(token, &in_squote, &in_dquote);
	if (n_of_quotes == 0)
		return ;
	temp = malloc(sizeof(char) * ((token->len - n_of_quotes) + 1));
	if (!temp)
	{
		ft_lstfirst(token)->status_code = ERROR_MALLOC;
		return ;
	}
	process_quotes(token, &temp, &in_squote, &in_dquote);
	if (temp)
	{
		free(token->content);
		token->content = temp;
	}
	token->len = ft_strlen(token->content);
}
