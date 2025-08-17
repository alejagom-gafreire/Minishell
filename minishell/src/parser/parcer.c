/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:18:03 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/30 17:28:54 by alejogogi        ###   ########.fr       */
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
	parcer->infile = -1;
	parcer->outfile = -1;
	parcer->name_infile = NULL;
	parcer->name_outfile = NULL;
	return (parcer);
}

static void	process_tokens(t_lexer **aux, t_parcer *new_parcer, char **cmd)
{
	while (*aux && (*aux)->token != T_PIPE)
	{
		if (*aux && (*aux)->token == T_REDIR_IN)
			*aux = (*aux)->next;
		else if (*aux && (*aux)->token == T_INFILE)
			*aux = handle_inflie((*aux), new_parcer);
		else if ((*aux)->token == T_HEREDOC)
			*aux = check_heredoc((*aux), new_parcer);
		else if ((*aux)->token == T_NAME_CMD)
			*aux = handle_cmd((*aux), cmd);
		else if (*aux && (*aux)->token == T_REDIR_OUT)
			*aux = handle_outfile((*aux), new_parcer);
	}
}

static void	finalize_parcer(t_parcer *new_parcer, char *cmd)
{
	if (cmd)
	{
		new_parcer->cmd_args = ft_strdup(cmd);
		free(cmd);
	}
}

t_parcer	*add_parcer(t_lexer *lexer)
{
	t_lexer		*aux;
	t_parcer	*parcer;
	t_parcer	*new_parcer;
	char		*cmd;

	parcer = NULL;
	aux = lexer;
	while (aux)
	{
		cmd = NULL;
		new_parcer = mem_parcer();
		if (!new_parcer)
			return (NULL);
		process_tokens(&aux, new_parcer, &cmd);
		finalize_parcer(new_parcer, cmd);
		if (aux && aux->token == T_PIPE)
			aux = aux->next;
		inside_parcer(&parcer, new_parcer);
	}
	return (parcer);
}
