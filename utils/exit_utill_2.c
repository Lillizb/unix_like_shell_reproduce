
#include "../minishell.h"

int	count_quotes_exit(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

int	is_number(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			i++;
			continue ;
		}
		else if (str[i] == '-')
			return (2);
		else if (str[i] == '"' || str[i] == '\'')
		{
			i++;
			continue ;
		}
		else if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	handle_exit(char **split_input, t_list **env_list, 
		char *input)
{
	if (!split_input[1])
	{
		exit_clean(env_list, split_input, input, 0);
	}
	if (is_number(split_input[1]) == 1)
		check_exit_code(split_input, env_list, input);
	else
	{
		perror("numeric argument required ");
		if (is_number(split_input[1]) == 1)
			exit_clean(env_list, split_input, input, 156);
		else if (is_number(split_input[1]) == 2)
			exit_clean(env_list, split_input, input, 156);
		else
			exit_clean(env_list, split_input, input, 2);
	}
}
