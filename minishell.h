#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "token_list/tokenlist.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define WHITESPACE 32
# define D_QUOTE 34
# define S_QUOTE 39

# define CMD 1
# define ARG 2
# define FLAG 3
# define TRUNC 4
# define APPEND 5
# define DOUBLE_INPUT 6
# define INPUT 7
# define PIPE 8
# define END 9

//CMDs
# define D_ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define ERROR_GENERAL 1
# define ERROR_MALLOC 2
# define ERROR_FORK 3
# define ERROR_DUP2 4
# define ERROR_EMPTY_VALUE 5
# define ERROR_WAITPID 6
# define ERROR_PIPE 7
# define ERROR_CMD_PTH_NOT_FOUND -1
# define ERROR_EXEC 127
# define ERROR_NO_FILE 126
# define ERROR_OPEN_QUOTE 130
# define SYNTAX_ERROR 2
//############################################################################//

//Global Variable
extern int	g_signal_code;

//############################################################################//

//Main
int		main(int argc, char **argv, char **envp);
int		check_input(char *input, t_list **env_list, int *status_code);
int		check_quotes(char *input);
int		validate_quotes(int n_of_squotes, int n_of_dquotes);
int		count_squotes(int *in_squote_string, int in_dquote_string,
			char *input, int i);
int		count_dquotes(int *in_dquote_string, int in_squote_string,
			char *input, int i);
int		is_number(const char *str);
int		count_quotes_exit(char *str);
void	setup_signals(void);
void	shell_routine(t_list **env_list, char *input,
			int n_of_token, int *status_code);
void	free_split_input(char **split_input);
void	handle_exit(char **split_input, t_list **env_list,
			char *input);
void	save_status_code(t_list *token_list, int *status_code);
void	exit_clean(t_list **env_list, char **split_input, char *input,
			int exit_code);
void	check_exit_code(char **split_input, t_list **env_list, char *input);
char	*get_exit_code(char *str);
void	check_signal_code(int *status_code);
void	cleanup_for_next_cmd(t_list **token_list, char **input);

//############################################################################//

//Lexer
t_list	*lexer(char *input, int n_of_token, t_list **env_list, int status_code);
t_list	*create_tkn_lst(t_list *token_list, char *input,
			int n_of_token, int status_code);
t_list	*create_and_init_token(t_list *token_list, char **input,
			int i, int status_code);
t_list	*init_tkn(t_list *token_list, t_list *new_token, int t_len, int i);
t_list	*move_to_list_head(t_list *current);
char	*skip_whitespace(char *input, int *j);
t_list	*split_string(t_list *token_list, char *input, int n_of_token);
t_list	*malloc_for_content(t_list *new_node);
void	skip_content_in_squotes(t_list **token_list, int *i, int *in_squote);
void	skip_content_in_dquotes(t_list **token_list, int *i, int *in_dquote);
void	init_lexer_tkn(t_list *new_token, int t_len, int i);
void	detect_redir_in_str(t_list **token_list, int *in_squote,
			int *in_dquote);
void	extract_redir(t_list **token_list, int j, int *in_dquote);
char	*allocate_redir_tmp(t_list **token_list, int redir_len, int in_dquote);
int		is_env_variable_ii(t_list *token_list, int i);
void	handle_quotes_env(t_list **token_list, int *i, int *in_squote, 
			int *in_dquote);
void	is_whitespace(int *j, t_list **token_list);
void	detect_env_in_str(t_list **token_list, int *in_squote, int *in_dquote);
int		handle_dquote(t_list **token_list, int *i, int *in_dquote, 
			int *in_squote);
int		handle_squote(t_list **token_list, int *i, int *in_squote,
			int *in_dquote);
void	find_return_code(t_list **token_list);	
void	return_code_routine(t_list **token_list, char *tmp, char *return_code);
void	detect_pipe_in_str(t_list **token_list, int *in_squote, int *in_dquote);
char	*allocate_pipe_tmp(t_list **token_list, int *in_dquote);
void	extract_pipe(t_list **token_list, int j, int *in_dquote);
t_list	*create_new_token(t_list **token_list, int t_len, int *in_dquote);
void	handle_dquote_content(t_list *new_token, t_list **token_list, 
			int t_len, int new_len);
void	split_before_value(t_list **token_list, int i, int j, int *in_dquote);
void	define_type(t_list *token);
int		check_empty_string(t_list **token_list, char *input, int *start);
int		count_token(char *input);
int		token_len(char *input);
void	if_in_quote(char *input, int *in_dquote_str, int *in_squote_str, int i);
void	print_token_list(t_list *token_list);

//############################################################################//

//Parser
t_list	*ft_parser(t_list *token_list, t_list **env_list);
t_list	*cmd_is_build_in(t_list *token_list, t_list **env_list);
void	handle_builtin_command(t_list *token_list, t_list **env_list);
int		count_pipes_set_cmd_index(t_list *token_list);

//############################################################################//

//Executor
int		simple_executor(t_list *token_list, t_list **env_list);
void	pipe_executor(t_list *token_list, t_list **env_list, int n_of_pipes);
int		prepare_for_execution(t_list *token_list, pid_t **pid,
			int ***fd, int n_of_pipes);
void	close_all_fds(int **fd, int n_of_pipes);
void	malloc_for_fd(t_list *token_list, int ***fd, int n_of_pipes);
void	malloc_for_pid(t_list *token_list, int **fd, pid_t **pid,
			int n_of_pipes);
int		check_for_heredoc(t_list *token_list);
void	create_pipes(t_list *token_list, int **fd, int n_of_pipes);
void	dup2_for_child(int **fd, int n_of_pipes, int i);
int		child_process_pipe(t_list **env_list, t_list **cmd_head);
void	print_pipe_result(t_list *cmd_head);
t_list	*find_next_cmd(t_list **cmd_head);
t_list	*find_last_cmd(t_list *cmd_head);
t_list	*jump_to_first_node(t_list **token_list);
void	close_and_free_fd(int **fd, int n_of_pipes);
int		prepare_token_and_env_arrays(t_list *token_list, t_list **env_list);

//############################################################################//

//Builtins

//ECHO
t_list	*ft_echo(t_list *token_list, t_list *env_list);
int		is_env_variable(t_list *token_list);
int		ft_echo_routine(t_list *token_list, t_list *env_list, char *env_value,
			size_t *total_len);
int		ft_total_len(t_list *token_list, char *env_value);
int		ft_handle_env_variable(t_list *token_list,
			char *env_value, size_t *total_len);
void	ft_add_to_result_echo(t_list **token_list, char *env_value,
			size_t *total_len);
void	ft_result_not_null(t_list **token_list, t_list **head,
			char *env_value, size_t *total_len);
void	ft_process_echo_tokens(t_list *token_list, t_list *env_list,
			size_t *total_len, char *env_value);
//PWD
void	ft_pwd(t_list *token_list);

//CD
int		ft_cd(t_list *token_list, t_list *env_list);
char	*ft_join_args(t_list *token_list);
int		calculate_total_len(t_list *token_list);
void	update_env(t_list *head, t_list **env_list, char **dir_path);

//ENV
t_list	*ft_allenv(t_list *token_list, t_list **env_list);
void	env_list_to_array_env(t_list *token_list, t_list **env_list);
t_list	*create_new_env_node(t_list *token_list, t_list *env_list,
			char *new_content);
void	create_env_content(t_list *token_list, char **new_content,
			char *name, char *value);

//UNSET
void	ft_unset_env(t_list *token_list, t_list **env_list);
char	*ft_get_varname(t_list *env_list);
void	prepare_token_for_unset(t_list **token_list);

//EXPORT
int		ft_export_env(t_list *token_list, t_list **env_list);
int		check_env_name(t_list *token_list);
int		first_pos_num_or_equal(t_list *token_list);
char	*ft_split_for_varname(t_list *token_list);
char	*ft_split_for_value(t_list *token_list);
void	ft_print_export_list(t_list *env_list);
void	ft_swap_content(t_list *a, t_list *b);
void	ft_sort_export_list(t_list *env_list);

//############################################################################//

//Execve
int		cmd_is_exec(t_list *token_list, t_list *env_list);
int		is_absolute_path(t_list *token_list, t_list *env_list);
void	get_env_path(t_list *token_list, t_list *env_list, char ***path);
int		count_token_elements(t_list *token_list);
int		count_env_elements(t_list *env_list);
int		check_args_helper(t_list *token, char **args);
char	**token_list_to_array_exec(t_list *token_list);
char	**env_list_to_array_exec(t_list *token_list, t_list *env_list);
void	add_cmd_to_path(t_list *token_list, char ***path_list);
void	remove_colon(char **path_list, int i);
int		create_run_process(t_list *token_list, char **org_path_list,
			char **env);
void	child_process(pid_t pid, t_list *token_list,
			char **path_list, char **env);
void	free_token_array(t_list **token_list);
void	free_env_array(t_list **token_list);
void	free_path_list(char **path_list);

//############################################################################//

//Envp
t_list	*create_env_list(char **envp, char *argv);
t_list	*init_env_list(t_list *env_list, t_list *new_node, int i, int j);
t_list	*change_shellname(t_list *env_list);
t_list	*create_new_env_node(t_list *token_list, t_list *env_list,
			char *new_content);
void	print_env_variable(char *var_name);
char	*ft_getenv(t_list *env_list, char *var);
void	ft_setenv(t_list *token_list, t_list *env_node,
			char *value, char *name);
void	ft_addenv(t_list *token_list, t_list *env_list,
			char *value, char *name);

//############################################################################//

//Redirects
int		handle_redir(t_list **token);
int		check_next_token(t_list **token_list);
int		handle_type(t_list **token, int *file);
int		handle_output_redirection(t_list **token);
int		open_output_file(t_list **token);
void	process_heredoc_input(int fd[2], t_list **token);
int		ft_add_new_token(t_list **token_list, char *tmp);
t_list	*ft_create_new_token(t_list **token_list, char *tmp, int *len);
void	ft_init_redir_tkn(t_list *new_token, int index, int len);
void	handle_heredoc(t_list **token);
int		check_fd(int fd);

//############################################################################//

//Pipe
void	handle_pipe(t_list *token);

//############################################################################//

//Signal
void	signal_handle_ctrlc(int sig); //handle ctrl+c - start a new line
void	cleanup_and_exit(t_list **list, int status_code);

//############################################################################//

//Utils
void	ft_remove_quotes(t_list *token_list);
int		count_quotes(t_list *token, int *in_squote, int *in_dquote);
void	process_quotes(t_list *token_list, char **temp,
			int *in_squote, int *in_dquote);
int		check_syntax_errors(t_list *token_list);

//############################################################################//

#endif
