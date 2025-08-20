/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-18 09:29:17 by gabriel           #+#    #+#             */
/*   Updated: 2025-08-18 09:29:17 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ===================== Expansión por tokens ===================== */
/* Reglas post-expansión:
   - T_INFILE/T_OUTFILE: si "" => error (ambiguous redirect)
   - T_NAME_CMD/T_GENERAL:
		* "" + kind == T_PLAIN => borrar token
		* "" + kind == T_DQ/T_SQ => conservar argumento vacío
   - Operadores: no se tocan
*/

/*
	delete_current:
	- Elimina el nodo actul de la listas enlazada del lexer
*/
static void	delete_current(t_lexer **head, t_lexer **prev, t_lexer **node)
{
	t_lexer	*dlt;

	dlt = *node;
	if (*prev == NULL)
	{
		*head = (*node)->next;
		*node = *head;
	}
	else
	{
		(*prev)->next = (*node)->next;
		*node = (*prev)->next;
	}
	free_lexer_node(dlt);
}

/*
	check_variable:
	- Chequea si el contenido requiere expansión
*/
static int	check_variable(t_lexer *node, int last_status)
{
	char	*expand;

	if (node->kind != T_DQ && node->kind != T_PLAIN)
		return (0);
	expand = expand_vars_two_pass(node->inf, last_status);
	if (!expand)
		return (1);
	free(node->inf);
	node->inf = expand;
	return (0);
}

/*
	(Revisar creo que no es necesario)
	handle_redir:
	- Se encarga de manejar las redirecciones
	- Chequea si esta vacio o espacios
*/
static int	handle_redir(t_lexer **prev, t_lexer **node)
{
	if (is_empty_tok(*node))
		return (printf("minishell: ambiguous redirect\n"), 1);
	advance_nodes(prev, node);
	return (0);
}

/*
	(Revisar creo que no es necesario)
	handle_plain_word:
	- Se encarga de chequear palabras planas
	- Chequea si esta vacio o espacios
*/
static int	handle_plain_word(t_lexer **head, t_lexer **prev, t_lexer **node)
{
	if (is_empty_tok(*node) && (*node)->kind == T_PLAIN)
	{
		delete_current(head, prev, node);
		return (1);
	}
	return (0);
}

/*
	expand_tokens:
	- Se encarga de aplicar cualquier funcion anterior
	- Chequea si esta vacio o espacios
*/
int	expand_tokens(t_lexer **lexer_list, int last_status)
{
	t_lexer	*node;
	t_lexer	*prev;

	if (!lexer_list)
		return (0);
	node = *lexer_list;
	prev = NULL;
	while (node)
	{
		if (is_word_token(node->token))
		{
			if (check_variable(node, last_status))
				return (1);
			if (node->token == T_INFILE || node->token == T_OUTFILE)
			{
				if (handle_redir(&prev, &node))
					return (1);
				continue ;
			}
			if ((node->token == T_NAME_CMD || node->token == T_GENERAL)
				&& handle_plain_word(lexer_list, &prev, &node))
				continue ;
		}
		advance_nodes(&prev, &node);
	}
	return (0);
}
