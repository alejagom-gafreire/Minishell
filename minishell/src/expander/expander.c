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

static void	delete_current(t_lexer **head, t_lexer **prev, t_lexer **node)
{
	t_lexer	*del;

	del = *node;
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
	free_lexer_node(del);
}

static int	expand_if_needed(t_lexer *node, int last_status)
{
	char	*e;

	if (node->kind != T_DQ && node->kind != T_PLAIN)
		return (0);
	e = expand_vars_two_pass(node->inf, last_status);
	if (!e)
		return (1);
	free(node->inf);
	node->inf = e;
	return (0);
}

static int	handle_redir(t_lexer **prev, t_lexer **node)
{
	if (is_empty_tok(*node))
		return (printf("minishell: ambiguous redirect\n"), 1);
	advance_nodes(prev, node);
	return (0);
}

static int	handle_plain_word(t_lexer **head, t_lexer **prev, t_lexer **node)
{
	if (is_empty_tok(*node) && (*node)->kind == T_PLAIN)
	{
		delete_current(head, prev, node);
		return (1);
	}
	return (0);
}

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
			if (expand_if_needed(node, last_status))
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
