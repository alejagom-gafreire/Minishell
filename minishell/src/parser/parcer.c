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

static char	*aux_parcer(char *cmd, char *sec)
{
	char	*res;
	char	*temp;

	res = NULL;
	temp = NULL;
	temp = ft_strjoin(cmd, " ");
	free(cmd);
	res = ft_strjoin(temp, sec);
	free(temp);
	return (res);
}

int	open_outfile(t_lexer **aux, t_parcer *new_node)
{
	int	fd;

	fd = -1;
	if (ft_strcmp((*aux)->inf, ">", 2) == 0)
	{
		fd = open((*aux)->next->inf, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perro("opoen");
			return (-1);
		}
	}
	else if (ft_strcmp((*aux)->inf, ">>", 3) == 0)
	{
		fd = open((*aux)->next->inf, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
		{
			perro("opoen");
			return (-1);
		}
	}
	return (fd);
}

static void	process_tokens(t_lexer **aux, t_parcer *new_parcer, char **cmd)
{
	while (*aux && (*aux)->token != T_PIPE)
	{
		if ((*aux)->token == T_REDIR_IN)
			*aux = (*aux)->next;
		if (*aux && (*aux)->token == T_INFILE)
		{
			//aqui manejar lo del heredoc.
			new_parcer->name_infile = ft_strdup((*aux)->inf);
			new_parcer->infile = open((*aux)->inf, O_RDONLY);
		}
		else if (*aux && (*aux)->token == T_REDIR_OUT)
		{
			if ((*aux)->next && (*aux)->next->token == T_OUTFILE)
			{
				new_parcer->name_outfile = ft_strdup((*aux)->next->inf);
				new_parcer->outfile = open_outfile((*aux), new_parcer);
			}
		}
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
