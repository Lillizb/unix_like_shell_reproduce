
#include "../minishell.h"

void	if_in_quote(char *input, int *in_dquote_str, int *in_squote_str, int i)
{
	if (input[i] == S_QUOTE && *in_dquote_str == 0)
		*in_squote_str = !(*in_squote_str);
	else if (input[i] == D_QUOTE && *in_squote_str == 0)
		*in_dquote_str = !(*in_dquote_str);
}

int	count_token(char *input)
{
	int	i;
	int	counter;
	int	in_token;
	int	in_squote_string;
	int	in_dquote_string;

	i = 0;
	counter = 0;
	in_token = 0;
	in_squote_string = 0;
	in_dquote_string = 0;
	while (input[i])
	{
		if_in_quote(input, &in_dquote_string, &in_squote_string, i);
		if (!in_squote_string && !in_dquote_string && input[i] == WHITESPACE)
			in_token = 0;
		else if (!in_token)
		{
			counter++;
			in_token = 1;
		}
		i++;
	}
	return (counter);
}

int	token_len(char *input)
{
	int	i;
	int	len;
	int	in_squote_string;
	int	in_dquote_string;

	i = 0;
	len = 0;
	in_squote_string = 0;
	in_dquote_string = 0;
	while (input[i] == WHITESPACE)
		i++;
	while (input[i])
	{
		if_in_quote(input, &in_dquote_string, &in_squote_string, i);
		if (input[i] == WHITESPACE && !in_squote_string && !in_dquote_string)
			break ;
		len++;
		i++;
	}
	return (len);
}
