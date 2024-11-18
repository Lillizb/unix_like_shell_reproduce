/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:56:58 by ygao              #+#    #+#             */
/*   Updated: 2024/10/05 17:25:07 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_exit_code(char *str)
{
	int		i;
	int		j;
	int		n_quotes;
	char	*tmp;

	i = 0;
	j = 0;
	n_quotes = count_quotes_exit(str);
	tmp = malloc(sizeof(char) * (ft_strlen(str) - n_quotes + 1));
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			i++;
		else if (str[i] == '"' || str[i] == '\'')
			i++;
		else if (str[i] >= '0' && str[i] <= '9')
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

void	check_exit_code(char **split_input, t_list **env_list, char *input)
{
	int		exit_code;
	char	*exit_code_arr;

	exit_code_arr = get_exit_code(split_input[1]);
	exit_code = ft_atoi(exit_code_arr);
	free(exit_code_arr);
	if (split_input[2])
	{
		perror("too many arguments ");
		exit_clean(env_list, split_input, input, 1);
	}
	else
		exit_clean(env_list, split_input, input, exit_code);
}

void	exit_clean(t_list **env_list, char **split_input,
		char *input, int exit_code)
{
	free_split_input(split_input);
	free(input);
	cleanup_and_exit(env_list, exit_code);
	exit(exit_code);
}
