/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:44:33 by ygao              #+#    #+#             */
/*   Updated: 2024/10/18 12:34:45 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_for_next_cmd(t_list **token_list, char **input)
{
	if (*input)
		free(*input);
	*input = NULL;
	if ((*token_list))
		ft_lstclear(token_list, free);
}

void	shell_routine(t_list **env_list, char *input,
	int n_of_token, int *status_code)
{
	t_list	*token_list;

	token_list = NULL;
	while (1)
	{
		input = readline("¯\\_(ツ)_/¯ : ");
		if (input == NULL)
		{
			if (token_list)
				ft_lstclear(&token_list, free);
			cleanup_and_exit(env_list, *status_code);
		}
		if (input[0] != '\0')
			add_history(input);
		if (check_input(input, env_list, status_code) == 1)
			continue ;
		save_status_code(token_list, status_code);
		n_of_token = count_token(input);
		token_list = lexer(input, n_of_token, env_list, *status_code);
		save_status_code(token_list, status_code);
		cleanup_for_next_cmd(&token_list, &input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	int		n_of_token;
	int		status_code;
	t_list	*env_list;

	input = NULL;
	n_of_token = 0;
	status_code = 0;
	env_list = NULL;
	setup_signals();
	if (argc != 1 && argv[0])
	{
		printf("Wrong input: usage > ./minishell\n");
		status_code = ERROR_GENERAL;
		return (1);
	}
	env_list = create_env_list(envp, input);
	if (!env_list)
	{
		printf("ENV list was not created\n");
		status_code = ERROR_GENERAL;
		return (1);
	}
	shell_routine(&env_list, input, n_of_token, &status_code);
	return (0);
}
