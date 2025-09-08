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
	parcer->building = NULL;
	parcer->infile = -1;
	parcer->outfile = -1;
	parcer->name_infile = NULL;
	parcer->name_outfile = NULL;
	parcer->syntax_error = 0;
	return (parcer);
}

static void	print_error_syntax(void)
{
	printf("error sintáctico cerca del elemento inesperado `newline'\n");
}

static void	process_tokens(t_lexer **aux, t_parcer *new_parcer)
{
	while (*aux && (*aux)->token != T_PIPE)
	{
		if (*aux && (*aux)->token == T_REDIR_IN)
			*aux = (*aux)->next;
		else if (*aux && (*aux)->token == T_INFILE)
			*aux = handle_inflie((*aux), new_parcer);
		else if ((*aux)->token == T_HEREDOC)
			*aux = check_heredoc((*aux), new_parcer);
		else if (*aux && (*aux)->token == T_BUILDINGS)
			*aux = check_buildings((*aux), new_parcer);
		else if ((*aux)->token == T_NAME_CMD || (*aux)->token == T_GENERAL)
			*aux = handle_cmd((*aux), new_parcer);
		else if (*aux && (*aux)->token == T_REDIR_OUT)
		{
			if ((*aux)->next)
				*aux = handle_outfile((*aux), new_parcer);
			else
			{
				print_error_syntax();
				*aux = NULL;
				new_parcer->syntax_error = 1;
				return ;
			}
		}
	}
}

// static void	finalize_parcer(t_parcer *new_parcer, char *cmd)
// {
// 	if (cmd)
// 	{
// 		new_parcer->cmd_args = ft_strdup(cmd);
// 		free(cmd);
// 	}
// }

t_parcer	*add_parcer(t_lexer *lexer)
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
		process_tokens(&aux, new_parcer);
		//finalize_parcer(new_parcer, cmd);
		if (aux && aux->token == T_PIPE)
			aux = aux->next;
		inside_parcer(&parcer, new_parcer);
	}
	return (parcer);
}
