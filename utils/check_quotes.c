
#include "../minishell.h"

int	validate_quotes(int n_of_squotes, int n_of_dquotes)
{
	if (n_of_squotes % 2 != 0)
	{
		printf("A single Quote is missing\n");
		return (1);
	}
	if (n_of_dquotes % 2 != 0)
	{
		printf("A double Quote is missing\n");
		return (1);
	}
	return (0);
}

int	count_squotes(int *in_squote_string, int in_dquote_string,
		char *input, int i)
{
	int	count_squotes;

	count_squotes = 0;
	if (input[i] == S_QUOTE && !in_dquote_string)
	{
		count_squotes++;
		*in_squote_string = !(*in_squote_string);
	}
	return (count_squotes);
}

int	count_dquotes(int *in_dquote_string, int in_squote_string,
		char *input, int i)
{
	int	count_dquotes;

	count_dquotes = 0;
	if (input[i] == D_QUOTE && !in_squote_string)
	{
		count_dquotes++;
		*in_dquote_string = !(*in_dquote_string);
	}
	return (count_dquotes);
}

int	check_quotes(char *input)
{
	int	i;
	int	n_of_squotes;
	int	n_of_dquotes;
	int	in_squote_string;
	int	in_dquote_string;

	i = 0;
	n_of_squotes = 0;
	n_of_dquotes = 0;
	in_squote_string = 0;
	in_dquote_string = 0;
	while (input[i])
	{
		n_of_squotes += count_squotes(&in_squote_string,
				in_dquote_string, input, i);
		n_of_dquotes += count_dquotes(&in_dquote_string,
				in_squote_string, input, i);
		i++;
	}
	if (validate_quotes(n_of_squotes, n_of_dquotes))
		return (1);
	return (0);
}
