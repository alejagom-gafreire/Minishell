/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:18:03 by alejogogi         #+#    #+#             */
/*   Updated: 2025/08/15 13:04:14 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parcer	*mem_parcer(void)
{
	t_parcer	*parcer;

	parcer = malloc(sizeof(t_parcer));
	if (!parcer)
		return (NULL);
	parcer->next = NULL;
	parcer->cmd_args = NULL;
	parcer->arg_export = NULL;
	parcer->argv = NULL;
	parcer->builtin = NULL;
	parcer->infile = -1;
	parcer->outfile = -1;
	parcer->name_infile = NULL;
	parcer->name_outfile = NULL;
	parcer->syntax_error = 0;
	parcer->redir_error = 0;

	parcer->argv = NULL;
	parcer->argc = 0;
	return (parcer);
}

void	print_error_syntax(void)
{
	printf("syntax error near unexpected token `newline'\n");
}

static void	process_tokens(t_lexer **aux, t_parcer *new_parcer, t_shell **env)
{
	while (*aux && (*aux)->token != T_PIPE)
	{
		if (new_parcer->redir_error || new_parcer->syntax_error)
			*aux = next_node((*aux));
		if (*aux && (*aux)->token == T_REDIR_IN)
			*aux = aux_redir_in((*aux), new_parcer);
		else if (*aux && (*aux)->token == T_DELIM)
			*aux = (*aux)->next;
		else if (*aux && (*aux)->token == T_INFILE)
			*aux = handle_infile((*aux), new_parcer);
		else if ((*aux)->token == T_HEREDOC)
			*aux = check_heredoc((*aux), new_parcer, env);
		else if (*aux && (*aux)->token == T_BUILTINS)
			*aux = check_buildings((*aux), new_parcer);
		else if (is_word_tok((*aux)))
			*aux = handle_cmd((*aux), new_parcer);
		else if (*aux && (*aux)->token == T_REDIR_OUT)
		{
			*aux = aux_redir_out((*aux), new_parcer, env);
		}
	}
}

t_parcer	*add_parcer(t_lexer *lexer, t_shell **env)
{
	t_lexer		*aux;
	t_parcer	*parcer;
	t_parcer	*new_parcer;

	parcer = NULL;
	aux = lexer;
	while (aux)
	{
		new_parcer = mem_parcer();
		if (!new_parcer)
			return (NULL);
		process_tokens(&aux, new_parcer, env);
		if (aux && aux->token == T_PIPE)
			aux = aux->next;
		inside_parcer(&parcer, new_parcer);
	}
	return (parcer);
}
