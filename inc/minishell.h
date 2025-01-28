/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:19:11 by jwhitley          #+#    #+#             */
/*   Updated: 2025/01/27 20:34:24 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <time.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# define NONE 0
# define S_QUOTE 1
# define D_QUOTE 2
# define UNCLOSED 3

# define IN 0
# define OUT 1

# define INFILE 0
# define HEREDOC 1
# define OUTFILE 2
# define APPEND 3
# define WORD 4
# define PIPE 5

# define ERROR_1 "Minishell: Error: Unexpected EOF: Unclosed "
# define ERROR_2 "Minishell: Error: Unexpected newline"
# define ERROR_3 "Minishell: Error: Unexpected token "
# define ERROR_4 "cd: error retrieving current directory: getcwd: cannot "
# define ERROR_4_2 "access parent directories: No such file or directory"
# define ERROR_5 "Minishell: Error: Incorrect option: Must be '-c'\n"
# define ERROR_6 "Minishell: Error: No argument provided\n"
# define ERROR_7 "Minishell: cd: too many arguments\n"
# define HERE_DOC_PATH "/tmp/.here_doc_temp" 

/* STRUCT TYPEDEFS */
typedef struct s_redir
{
	char			*filename;
	int				direction;
	int				mode;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char				*cmd;
	char				**args;
	int					pid;
	int					fd_in;
	int					fd_out;
	int					pipe_fd[2];
	int					cmd_n;
	char				**env;
	struct s_data		*data;
	struct s_redir		*redir;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_tokens
{
	char				*word;
	char				*sep;
	int					i;
	int					type;
	int					start;
	int					end;
	int					q_status;
	bool				processed;
	struct s_data		*data;
	struct s_tokens		*next;
	struct s_tokens		*prev;
}	t_tokens;

typedef struct s_data
{
	char				*user_input;
	struct s_tokens		*tokens;
	struct s_cmd		*cmds;
	char				**env;
	struct sigaction	sig_act;
}	t_data;

extern int	g_last_signal;

/* FUNCTION PROTOTYPES*/
/* init_data_struct.c */
t_data					*init_data_struct(char **env);

/* free.c */
void					free_data_struct(t_data *data, bool keep_env);
void					free_array(char **array);
void					multi_free(int count, ...);

/* free_list_clear.c */
void					token_lstclear(t_tokens *tokens);

/* get_input.c */
bool					valid_input(char *input);
char					*get_input(t_data *data);

/* process_user_input.c */
bool					process_user_input_non_int(t_data *data, char *av2);
bool					process_user_input(t_data *data);

/* token_splitter.c */
void					add_spaces(char **input, int *index, int new_spaces);
char					**split_tokens(char **input);

/* token_expand.c */
void					expand_tok_var(t_tokens *tok);
bool					check_and_expand_tokens(t_tokens *token);

/* token_expand_utils.c */
void					expand_tilde(t_tokens *tok);
void					remove_tok_quotes(t_tokens *tok);
void					find_section_end(t_tokens *tok);

/* token_str_join.c */
int						token_str_join(t_tokens *tok, char *new_var,
							int var_name_len, char *var_name);

/* token_syntax.c */
bool					sep_syntax(t_tokens *token);
bool					word_syntax(char *str);

/* token_list.c */
t_tokens				*token_lstnew(t_data *data, char *word, char *sep);
bool					token_list(t_data *data, char **split);

/* token_utils.c */
int						set_status(char c);
int						check_sep_spacing(char *input, int i);
void					set_token_type(t_tokens *token);
bool					is_a_separator(char c);

/* token_process_heredoc.c */
bool					process_heredoc(t_data *data, char *delimiter);

/* token_heredoc_var_insert.c */
int						hd_var_insert(t_tokens *temp, char *new_var,
							char *var_name);

/* cmd_list.c */
void					cmd_list_clear(t_cmd *cmds);
t_cmd					*get_cmds(t_data *data);

/* cmd_list_utils.c */
char					*parse_cmd(t_tokens *tokens, int start, int end);
int						cmd_find_end(int start, t_tokens *tokens);
int						cmd_count(t_tokens *tokens);

/* cmd_list_parse_args.c */
char					**parse_cmd_args(t_tokens *tokens, int start, int end);

/* redir_list.c */
void					redir_list_clear(t_redir *redir);
t_redir					*get_redir_list(t_tokens *tokens, int start, int end);

/* signal_handling.c */
void					standard_behavior(int sigint);
void					here_doc_open_behavior(int sig);

/* builtin_cd.c */
void					change_dir(t_cmd *cmd);

/* builtin_cd_utils.c */
void					go_home_sysenv(t_data *data);
void					go_home_expand_sysenv(t_data *data, char *new_dir);

/* builtin_echo.c */
void					echo_cmd(t_cmd *cmd);

/* builtin_execution_handling.c */
int						redirection_and_execution_builtin(t_cmd *cmd);
bool					is_a_builtin(t_cmd *cmd);

/* builtin_exit.c */
void					exit_cmd(t_data *data);

/* builtin_pwd.c */
void					print_pwd(t_data *data);

/* builtin_var_export.c */
bool					export_env(t_data *data, char *new_var);
bool					remove_var(t_data *data, char *var);

/* builtin_var_export_2.c */
void					print_ascii_sorted_env(t_data *data);

/* builtin_var_export_utils.c */
void					unset_env_all_arg(t_cmd *cmd);
void					export_env_all_arg(t_cmd *cmd);
bool					var_is_valid(char *new_var);

/* builtin_var_get_print.c */
void					print_env(t_data *data);
char					*get_var(char **env, char *var);

/* builtin_var_utils.c */
char					*find_var(char **env, char *var);

/* check_builtins.c */
bool					check_builtins(t_cmd *cmd);

/* execution_handling.c */
int						execute_command(t_cmd *command_array);
void					processing_commands(t_cmd *command_array);
void					shell_execution(t_cmd *command_array);

/* fetch_path_command.c */
char					**get_path_array(char **env, char *arg);
int						exec_command(char **env, char **arg);

/* multi_procesing.c */
void					waiting_sons_processes(t_cmd *command_array,
							int *status);

/* redirection_file_opening.c */
int						open_file(t_redir *redirection);

/* redirection_handling.c */
void					redirection_file_checking_and_selection(
							t_cmd **command_array);
void					redirection_and_execution(t_cmd *command_array);
void					redirecting_std_input(t_cmd *command_array);
void					redirecting_std_output(t_cmd *command_array);

/* utils.c */
bool					command_option(char *str);
bool					is_whitespace(char *str);
char					*get_realpwd(void);

/* DEBUG_FUNCS */
void					db_print_array(char **array);
void					db_print_tokens(t_data *data);
void					db_print_cmds(t_data *data);
void					db_print_redir(t_redir *input);

#endif
