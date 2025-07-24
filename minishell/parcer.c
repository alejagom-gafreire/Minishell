/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:18:03 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/24 20:00:13 by alejogogi        ###   ########.fr       */
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
	parcer->name_infile = NULL;
	parcer->name_outfile = NULL;
	return (parcer);
}

static char	*aux_parcer(char *cmd, char *sec)
{
	char	*res;

	res = NULL;
	res = ft_strjoin(cmd, " ");
	free(cmd);
	res = ft_strjoin(res, sec);
	return (res);
}

static void	process_tokens(t_lexer **aux, t_parcer *new_parcer, char **cmd)
{
	while (*aux && (*aux)->token != T_PIPE)
	{
		if ((*aux)->token == T_REDIR_IN)
			*aux = (*aux)->next;
		if (*aux && (*aux)->token == T_INFILE)
			new_parcer->name_infile = ft_strdup((*aux)->inf);
		else if (*aux && (*aux)->token == T_OUTFILE)
			new_parcer->name_outfile = ft_strdup((*aux)->inf);
		else if ((*aux)->token == T_NAME_CMD)
		{
			if (!*cmd)
				*cmd = ft_strdup((*aux)->inf);
			else
				*cmd = aux_parcer(*cmd, (*aux)->inf);
		}
		*aux = (*aux)->next;
	}
}

static void	finalize_parcer(t_parcer **parcer, t_parcer *new_parcer, char *cmd)
{
	if (cmd)
	{
		new_parcer->cmd_args = ft_strdup(cmd);
		free(cmd);
	}
	inside_parcer(parcer, new_parcer);
}

void	add_parcer(t_lexer *lexer, t_parcer **parcer)
{
	t_lexer		*aux;
	t_parcer	*new_parcer;
	char		*cmd;

	aux = lexer;
	while (aux)
	{
		cmd = NULL;
		new_parcer = mem_parcer();
		if (!new_parcer)
			return ;
		process_tokens(&aux, new_parcer, &cmd);
		finalize_parcer(parcer, new_parcer, cmd);
		if (aux && aux->token == T_PIPE)
			aux = aux->next;
	}
}
