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
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

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
	T_BUILDINGS,
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

typedef struct s_parcer
{
	int				infile;
	int				outfile;
	char			*cmd_args;
	char			*name_infile;
	char			*name_outfile;
	struct s_execute *exec;
	struct s_parcer	*next;
}					t_parcer;

typedef struct s_mini
{
	int				num_cmd;
	int				last_status; //variable para el $
	t_parcer		*parcer;
	t_lexer			*lexer;
}					t_mini;

// execute
int					init_pipes(t_mini *mini, int pipes[][2]);
int					safe_pipes(t_mini *mini, int (**pipes)[2]);
void				close_pipes(int pipes[][2], int num_pipes);
void				execute_cmd(t_mini *mini, char **envp);

// proccess_execve
int					wait_childrens(pid_t *pids, int num_cmd);
void				fd_redirect(t_parcer **list, int *i, t_mini *mini,
						int pipes[][2]);
void				exec_cmd(t_parcer *list, char **envp);
void				init_proccess(t_mini *mini, pid_t *pids,
						int pipes[][2], char **envp);

// execute_aux
void				free_split(char **split);
char				*get_path_env(char **envp);
char				*check_absolute_path(char *cmd);
char				*build_path(char *dir, char *cmd);
char				*find_executable(char *cmds, char **envp);

// lexer
int					check_token(int argc, char *argv[], char **envp);
void				check_line(char *line, char **envp);

// expander
int					expand_tokens(t_lexer **lexer_list, int last_status);
char				*itoa_status(int st, char buf[32]);
char				*dup_cstr(const char *s);
// functios print
void				print_parcer(t_parcer *parcer);
void				print_tokens(t_lexer *lexer);

// parser
t_parcer			*add_parcer(t_lexer *lexer);
void				inside_parcer(t_parcer **head, t_parcer *new_node);

//parser_aux
int					open_outfile(char *file, int appened);
int					read_heredoc(char *delim);

//parser handles
t_lexer				*handle_inflie(t_lexer *aux, t_parcer *new_parcer);
t_lexer				*check_heredoc(t_lexer *aux, t_parcer *new_parcer);
t_lexer				*handle_outfile(t_lexer *aux, t_parcer *new_parcer);
t_lexer				*handle_cmd(t_lexer *aux, char **cmd);

// lexer quotes
int					check_quotes(char *line, int i, t_lexer **lexer_list);
int					check_simple_quotes(char *line, int pos);
int					check_double_quotes(char *line, int pos);
void				num_comands(t_mini *mini);

// lexer token
void				add_token(t_lexer **lexer, char *info, t_tokens type,
						t_kind kind);
// lexer_aux
int					handle_word(char *line, int i, t_lexer **lexer_list,
						int *first_word);
int					handle_double_quotes(char *line, int i,
						t_lexer **lexer_list);
int					handle_simple_quotes(char *line, int i,
						t_lexer **lexer_list);
int					check_redirect(char *line, int i, t_lexer **lexer_list,
						int *first_word);
int					handle_output_redirect(char *line, int i,
						t_lexer **lexer_list);
int					handle_input_redirect(char *line, int i,
						t_lexer **lexer_list);
void				handle_pipe(t_lexer **lexer_list, int *first_word);
t_tokens			compare_buildings(char *word);

// signals
void				init_signals(void);
// free
void				free_minishell(t_mini *mini);
void				free_lexer(t_lexer *lexer);

#endif