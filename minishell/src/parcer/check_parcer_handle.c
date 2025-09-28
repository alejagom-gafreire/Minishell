/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parcer_handle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-12 11:57:48 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-12 11:57:48 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_arg(t_parcer *cmd, const char *s)
{
	char	**newv;
	int		i;

	if (!s)
		return (0);
	newv = (char **)malloc(sizeof(char *) * (cmd->argc + 2));
	if (!newv)
		return (1);
	i = 0;
	while (i < cmd->argc)
	{
		newv[i] = cmd->argv[i];
		i++;
	}
	newv[i] = ft_strdup(s);
	if (!newv[i])
		return (free(newv), 1);
	newv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = newv;
	cmd->argc++;
	return (0);
}

int	is_word_tok(t_lexer *n)
{
	if (!n)
		return (0);
	if (n->token == T_GENERAL || n->token == T_NAME_CMD)
		return (1);
	if (n->kind == T_SQ || n->kind == T_DQ)
		return (1);
	if (n->token == T_GENERAL)
		return (1);
	return (0);
}

t_lexer	*check_heredoc(t_lexer *aux, t_parcer *new_parcer, t_shell **env)
{
	if (aux->next && aux->next->token == T_DELIM)
	{
		new_parcer->infile = read_heredoc(aux->next->inf, (*env));
		if (new_parcer->infile == -1)
		{
			(*env)->error_heredoc = 1;
			return (aux->next);
		}
		return (aux->next->next);
	}
	else
	{
		printf("syntax error near unexpected token '%s'\n", aux->next->inf);
		new_parcer->syntax_error = 1;
		return (NULL);
	}
}

t_lexer	*handle_cmd(t_lexer *aux, t_parcer *new)
{
	if (!aux)
		return (NULL);
	if (is_word_tok(aux))
	{
		if (append_arg(new, aux->inf))
			new->syntax_error = 1;
		return (aux->next);
	}
	if (aux->token == T_GENERAL)
	{
		new->arg_export = ft_strdup(aux->inf);
		return (aux->next);
	}
	return (aux->next);
}

t_lexer	*check_buildings(t_lexer *aux, t_parcer *new_parcer)
{
	if (!aux)
		return (NULL);
	new_parcer->builtin = ft_strdup(aux->inf);
	if (!new_parcer->builtin)
		return (NULL);
	if (append_arg(new_parcer, aux->inf))
		new_parcer->syntax_error = 1;
	return (aux->next);
}
