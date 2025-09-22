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

t_lexer	*check_heredoc(t_lexer *aux, t_parcer *new_parcer, t_shell **env)
{
	if (aux->next && aux->next->token == T_DELIM)
	{
		new_parcer->infile = read_heredoc(aux->next->inf, (*env));
		if (new_parcer->infile == -1)
		{
			(*env)->error_heredoc = 1;
			return(aux->next);
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
	if (!new->cmd_args && is_word_tok(aux))
	{
		new->cmd_args = ft_strdup(aux->inf);
		return (aux->next);
	}
	if (new->cmd_args && is_word_tok(aux->last))
	{
		new->cmd_args = aux_parcer(new->cmd_args, aux->inf);
		return (aux->next);
	}
	if (aux->token == T_GENERAL)
	{
		new->arg_export = ft_strdup(aux->inf);
		return (aux->next);
	}
	return (aux->next);
}

// t_lexer	*handle_cmd(t_lexer *aux, t_parcer *new)
// {
//	if (!aux)
// 	return (NULL);
// if (!new->cmd_args && aux->token == T_NAME_CMD)
// {
// 	new->cmd_args = ft_strdup(aux->inf);
// 	return (aux->next);
// }
// else if (new->cmd_args && aux->last->token == T_NAME_CMD)
// {
// 	new->cmd_args = aux_parcer(new->cmd_args, aux->inf);
// 	return (aux->next);
// }
// if (aux->token == T_GENERAL)
// 	new->arg_export = ft_strdup(aux->inf);
// return (aux->next);
// }

t_lexer	*check_buildings(t_lexer *aux, t_parcer *new_parcer)
{
	if (!aux)
		return (NULL);
	new_parcer->builtin = ft_strdup(aux->inf);
	if (!new_parcer->builtin)
		return (NULL);
	return (aux->next);
}
