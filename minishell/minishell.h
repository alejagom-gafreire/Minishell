/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:10:34 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/23 22:17:15 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "./libft/libft.h"

typedef enum tokens
{
	T_NAME_CMD,  // grep ls echo etc....
	T_PIPE,      // |
	T_REDIR_IN,  // < , << simbolos.
	T_REDIR_OUT, // > >> simbolos.
	T_INFILE,    // primer txt.
	T_OUTFILE,   // salida del txt ultimo.
	T_GENERAL    // otras cosas.
}					tokens;

typedef struct s_lexer
{
	int				id;
	char			*inf;
	tokens			token;
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

// typedef	struct  s_mini
// {
// 	t_parcer *parcer;
// 	t_lexer	*lexer;
// }		t_mini; //revisar estructutra global para liberar memoria a futuro.

//lexer
int					check_token(int argc, char *argv[]);
void				check_line(char *line);

//parser
void				add_parcer(t_lexer *lexer, t_parcer **parcer);
void				print_parcer(t_parcer *parcer);//borrar

#endif