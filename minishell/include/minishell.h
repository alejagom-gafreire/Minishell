/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:10:34 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/08 10:05:52 by gafreire         ###   ########.fr       */
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

#define	READ_END  0
#define WRITE_END 1
/*
	T_NAME_CMD => "grep ls echo etc...."
	T_PIPE => "|"
	T_REDIR_IN => "< , << simbolos."
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
	T_REDIR_IN,
	T_REDIR_OUT,
	T_INFILE,
	T_OUTFILE,
	T_GENERAL
}					t_tokens;

typedef struct s_lexer
{
	int				id;
	char			*inf;
	t_tokens		token;
	t_tokens		last_token;
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
	struct s_parcer	*next;
}					t_parcer;

typedef struct s_mini
{
	int	num_cmd;
	t_parcer		*parcer;
	t_lexer			*lexer;
}					t_mini;

// execute
//void				create_process(t_mini *mini, char **envp);
void				free_split(char **split);
char				*find_executable(char *cmd, char **envp, t_execute *exec);
char				*check_absolute_path(char *cmd);
char				*get_path_env(char **envp);
// void 				create_child_processes(t_mini *mini, t_parcer *list, char **envp);

//execute.c
void    start_execute(t_mini *mini, char **envp);
int		init_pipes(int	cmds, int pipes[cmds - 1][2]);
void	init_forks(int (*pipes)[2], pid_t *pids, char **envp, t_mini *mini);
void	child_process(int i, int cmds, int pipes[cmds - 1][2], t_parcer *list, char **envp);
void	execute_command(t_parcer *list, char **envp);
void	handle_redirecitons(t_parcer *list);

//execute one command
void    execute_cmd(t_mini *mini, char **envp);
void	exec_cmd(t_parcer *list, char **envp);
t_execute	*init_exec(void);

// lexer
int					check_token(int argc, char *argv[], char **envp);
void				check_line(char *line, char **envp);
// functios print
void				print_parcer(t_parcer *parcer);
void				print_tokens(t_lexer *lexer);

// parser
t_parcer			*add_parcer(t_lexer *lexer);
void				inside_parcer(t_parcer **head, t_parcer *new_node);

// lexer quotes
int					check_quotes(char *line, int i, t_lexer **lexer_list);
int					check_simple_quotes(char *line, int pos);
int					check_double_quotes(char *line, int pos);
void				num_comands(t_mini *mini);

// lexer token
void				add_token(t_lexer **lexer, char *info, t_tokens type);
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

// free
void				free_minishell(t_mini *mini);
void				free_lexer(t_lexer *lexer);

#endif