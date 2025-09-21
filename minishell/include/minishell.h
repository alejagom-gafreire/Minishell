/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:10:34 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/12 15:41:38 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

#define RESET   "\001\033[0m\002"
#define CYAN    "\001\033[36m\002"
#define GREEN   "\001\033[32m\002"
#define BLUE    "\001\033[34m\002"
#define BOLD    "\001\033[1m\002"

#define BRIGHT_RED     "\x1b[91m"
#define BRIGHT_GREEN   "\x1b[92m"
#define BRIGHT_YELLOW  "\x1b[93m"
#define BRIGHT_BLUE    "\x1b[94m"
#define BRIGHT_MAGENTA "\x1b[95m"
#define BRIGHT_CYAN    "\x1b[96m"
#define BRIGHT_WHITE   "\x1b[97m"

# define READ_END 0
# define WRITE_END 1
/*
	T_NAME_CMD => "grep ls echo etc...."
	T_PIPE => "|"
	T_REDIR_IN => "< , << simbolos."
	T_HEREDOC =>  "simbolo <<"
	T_DELIM => "delimitador del heredoc"
	T_REDIR_OUT => "> >> simbolos."
	T_REDIR_OUT => "> >> simbolos."
	T_INFILE => "primer txt."
	T_OUTFILE => "salida del txt ultimo."
	T_GENERAL => "otras cosas."
*/
typedef unsigned int useconds_t;

typedef enum tokens
{
	T_NAME_CMD,
	T_PIPE,
	T_HEREDOC,
	T_DELIM,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_INFILE,
	T_OUTFILE,
	T_GENERAL,
	T_BUILTINS,
}					t_tokens;

/*
	PLAIN -> fuera de comillas
	DQ -> comillas dobles
	SQ -> comillas simples
*/
typedef enum kind
{
	T_PLAIN,
	T_DQ,
	T_SQ
}					t_kind;

/*
	id -> id del argv
	inf -> valor del argv
	token -> t_token
	last_token -> anterior t_token
	kind -> t_kind para manejar comillas
	la lista esta doblemente enlazada
*/
typedef struct s_lexer
{
	int				id;
	char			*inf;
	t_tokens		token;
	t_tokens		last_token;
	t_kind			kind;
	struct s_lexer	*next;
	struct s_lexer	*last;
}					t_lexer;

/*
	infile -> id infile
	outfile -> id outile
	cmd_args -> argumentos del comando
	builtin -> builtin detectado
	name_infile -> nombre infile
	name_outfile -> nombre outile
	syntax_error -> error que devuelve
	syntax_error -> error que devuelve si falla las redirreciones
*/
typedef struct s_parcer
{
	int				infile;
	int				outfile;
	char			*cmd_args;
	char			**argv;
	char			*arg_export;
	char			*builtin;
	char			*name_infile;
	char			*name_outfile;
	int				syntax_error;
	int				redir_error;
	struct s_parcer	*next;
}					t_parcer;

/*
	envi -> nuestro env
	last_status -> valor del status '$?'
*/
typedef struct s_shell
{
	char			**envi;
	int				last_status;
	int				error_heredoc;
}					t_shell;

/*
	num_cmd -> numero de comandos
*/
typedef struct s_mini
{
	int				num_cmd;
	t_parcer		*parcer;
	t_lexer			*lexer;
}					t_mini;

// execute
int					init_pipes(t_mini *mini, int pipes[][2]);
int					safe_pipes(t_mini *mini, int (**pipes)[2]);
void				close_pipes(int pipes[][2], int num_pipes);
void				execute_cmd(t_mini *mini, t_shell *envp);

// proccess_execve
int					wait_childrens(pid_t *pids, int num_cmd);
void				init_proccess(t_mini *mini, pid_t *pids, int pipes[][2],
						t_shell *envp);
char				**builtin_argv(const char *name, const char *args_str);
void				exec_cmd(t_parcer *list, char **envp);
void				fd_redirect(t_parcer **list, int *i, t_mini *mini,
						int pipes[][2]);

// built-ints
t_tokens			compare_builtins(char *word);
int					exec_env(t_shell *envp, t_parcer *list);
int					exec_exit(char **argv);
int					exec_builtins(t_parcer *list, char **argv, t_shell *envp);
int					exec_cd(char **cmd, t_shell *envp);
int					exec_echo(char **cmd);
int					exec_pwd(void);
int					ft_unset(t_shell *envi, t_parcer *list);

// ft_export
int					ft_export(t_shell *envp, t_parcer *list);
int					print_sorted(t_shell *envp);
int					cmp_env(const void *a, const void *b);
int					valid_args(char *arg);
int					cmp_env_key(const char *env, const char *arg,
						size_t key_len);
void				add_update_env(char *arg, char ***envi);
char				**all_args(char *args);
size_t				len_equal(char **equal, char *arg);

// execute_aux
void				free_split(char **split);
char				*get_path_env(char **envp);
char				*check_absolute_path(char *cmd);
char				*build_path(char *dir, char *cmd);
char				*find_executable(char *cmds, char **envp);

// lexer
int					check_token(char **envp);
void				check_line(char *line, t_shell *envp);

// expander
int					expand_tokens(t_lexer **lexer_list, t_shell *envp);
char				*itoa_status(int st, char buf[32]);
char				*dup_cstr(const char *s);
void				free_lexer_node(t_lexer *node);
size_t				measure_expanded_len(const char *str, t_shell *envp);
void				write_expanded(char *dst, const char *s, t_shell *envp);
char				*expand_vars_two_pass(const char *str, t_shell *envp);
int					is_var_char(char c);
int					is_var_start(char c);
int					is_word_token(int t);
void				advance_nodes(t_lexer **prev, t_lexer **node);
int					is_empty_tkn(t_lexer *n);
size_t				scan_var_end(const char *s, size_t start);
char				*get_env(char *name, char **envp);
// functios print
void				print_parcer(t_parcer *parcer);
void				print_tokens(t_lexer *lexer);

// parser
t_parcer			*add_parcer(t_lexer *lexer, t_shell **env);
void				inside_parcer(t_parcer **head, t_parcer *new_node);
int					is_word_tok(t_lexer *n);

// parser_aux
int					open_outfile(char *file, int appened);
int					read_heredoc(char *delim, t_shell **env);
void				restart_signals_shell(void);
void				init_signals_herecod(void);

// parser handles
t_lexer				*handle_infile(t_lexer *aux, t_parcer *new_parcer);
t_lexer				*check_heredoc(t_lexer *aux, t_parcer *new_parcer, t_shell **env);
t_lexer				*handle_outfile(t_lexer *aux, t_parcer *new_parcer, t_shell **env);
t_lexer				*handle_cmd(t_lexer *aux, t_parcer *new_node);
t_lexer				*check_buildings(t_lexer *aux, t_parcer *new_parcer);

// lexer quotes
int					check_simple_quotes(char *line, int pos);
int					check_double_quotes(char *line, int pos);
void				num_comands(t_mini *mini);

// lexer token
void				add_token(t_lexer **lexer, char *info, t_tokens type,
						t_kind kind);
// lexer_aux
int					handle_word(char *line, int i, t_lexer **lexer_list,
						int *first_word);
int					check_redirect(char *line, int i, t_lexer **lexer_list,
						int *first_word);
int					handle_output_redirect(char *line, int i,
						t_lexer **lexer_list);
int					handle_input_redirect(char *line, int i,
						t_lexer **lexer_list);
void				handle_pipe(t_lexer **lexer_list, int *first_word);

// promnt
char				**check_enviroment(char **envp);
void				print_banner(void);
void				spinner_loading(void);
int					show_menu(void);
void				print_names(int	options);
char				*create_prompt(void);
void				print_slow(const char *str, useconds_t delay);

// signals
void				init_signals(void);
// free
void				free_minishell(t_mini *mini);
void				free_lexer(t_lexer *lexer);
void				free_shell(t_shell *envi);

#endif
