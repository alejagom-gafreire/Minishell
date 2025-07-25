/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:10:34 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/25 15:58:09 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
	struct s_lexer	*next;
	struct s_lexer	*last;
}					t_lexer;

typedef struct s_parcer
{
	char			*cmd_args;
	char			*name_infile;
	char			*name_outfile;
	struct s_parcer	*next;
}					t_parcer;

typedef	struct  s_mini
{
	t_parcer *parcer;
	t_lexer	*lexer;
}		t_mini;

// lexer
int					check_token(int argc, char *argv[]);
void				check_line(char *line);

// parser
void				add_parcer(t_lexer *lexer, t_parcer **parcer);
void				print_parcer(t_parcer *parcer);
void				inside_parcer(t_parcer **head, t_parcer *new_node);

// lexer quotes
int					check_simple_quotes(char *line, int pos);
int					check_double_quotes(char *line, int pos);
// lexer token
void				add_token(t_lexer **lexer, char *info, t_tokens type);
//lexer_aux
int	handle_word(char *line, int i, t_lexer **lexer_list, int *last_token, int *first_word);
int	handle_double_quotes(char *line, int i, t_lexer **lexer_list);
int	handle_simple_quotes(char *line, int i, t_lexer **lexer_list);
int	handle_output_redirect(char *line, int i, t_lexer **lexer_list, int *last_token);
int	handle_input_redirect(char *line, int i, t_lexer **lexer_list, int *last_token);
void	handle_pipe(t_lexer **lexer_list, int *last_token, int *first_word);

#endif