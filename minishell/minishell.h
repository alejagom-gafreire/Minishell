/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:10:34 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/21 19:16:37 by gafreire         ###   ########.fr       */
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

typedef enum Tokens
{
	T_NAME_CMD, // grep ls echo etc....
	T_PIPE, // |
	T_REDIR_IN, // < , << simbolos.
	T_REDIR_OUT, // > >> simbolos.
	T_INFILE, //primer txt.
	T_OUTFILE, //salida del txt ultimo.
	T_GENERAL //otras cosas.
}		Tokens;

typedef struct s_lexer
{
	int	id;
	char *inf;
	enum tokens;
	t_lexer *next;
	t_lexer *last;
}		t_lexer;

typedef struct s_parcer
{
	char *cmd_args;
	char *name_infile;
	char *name_outfile;
	t_parcer *next;
}		t_parcer;

int		check_token(int argc, char *argv[]);
void	check_line(char *line);

#endif