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

int is_word_tok(t_lexer *n)
{
    if (!n) return 0;
    // Palabras "normales"
    if (n->token == T_GENERAL || n->token == T_NAME_CMD)
        return 1;
    // Palabras que vienen de comillas (tu debug dice kind 1 cuando hay comillas)
    // Si en tu proyecto los tipos de comillas están en 'kind', deja esta línea:
    if (n->kind == T_SQ || n->kind == T_DQ)
        return 1;
    // Si en tu proyecto las comillas usan un token propio (por ej. T_QUOTED == 8),
    // añade también:
    if (n->token == T_GENERAL /* el que corresponda a 'tipo 8' */)
        return 1;
    return 0;
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

t_lexer	*check_heredoc(t_lexer *aux, t_parcer *new_parcer)
{
	if (aux->next && aux->next->token == T_DELIM)
	{
		new_parcer->infile = read_heredoc(aux->next->inf);
		return (aux->next->next);
	}
	else
	{
		printf("syntax error near unexpected token '%s'\n", aux->next->inf);
		new_parcer->syntax_error = 1;
		return (NULL);
	}
}
t_lexer *handle_cmd(t_lexer *aux, t_parcer *new)
{
    if (!aux)
        return NULL;

    /* 1) Si aún no hay comando, la primera PALABRA (sea quoted o no) es el cmd */
    if (!new->cmd_args && is_word_tok(aux))
    {
        new->cmd_args = ft_strdup(aux->inf);   // << ANTES metías esto en cmd_args
        return aux->next;
    }

    /* 2) Si ya hay cmd, cualquier otra PALABRA va a los argumentos del cmd */
    if (new->cmd_args && is_word_tok(aux->last))
    {
        new->cmd_args = aux_parcer(new->cmd_args, aux->inf);
        return aux->next;
    }

    /* 3) Caso específico de export: solo tocar si de verdad estás en export */
    if (aux->token == T_GENERAL)
    {
        new->arg_export = ft_strdup(aux->inf);
        return aux->next;
    }

    /* 4) Por defecto avanza */
    return aux->next;
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
