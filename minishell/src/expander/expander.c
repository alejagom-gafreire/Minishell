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


/* Post-expansion rules:
   - T_INFILE/T_OUTFILE: if "" => error (ambiguous redirect)
   - T_NAME_CMD/T_GENERAL:
        * "" + kind == T_PLAIN => delete token
        * "" + kind == T_DQ/T_SQ => keep empty argument
   - Operators: unchanged
*/

/*
	delete_current:
	- Deletes the current node from the lexer's linked list
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
	handle_plain_word:
	- Se encarga de chequear palabras planas
	- Chequea si esta vacio o espacios
*/
static int	handle_redir(t_lexer **prev, t_lexer **node)
{
	if (is_empty_tkn(*node))
		return (printf("minishell: ambiguous redirect\n"), 1);
	advance_nodes(prev, node);
	return (0);
}

/*
	handle_plain_word:
	- Handles plain words
	- Checks if it is empty or only spaces
*/
static int	handle_plain_word(t_lexer **head, t_lexer **prev, t_lexer **node)
{
	if (is_empty_tkn(*node) && (*node)->kind == T_PLAIN)
	{
		delete_current(head, prev, node);
		return (1);
	}
	return (0);
}

/*
	expand_tokens:
	- Applies any of the previous functions
	- Checks if it is empty or only spaces
*/
int	expand_tokens(t_lexer **lst, t_shell *envp)
{
	t_lexer	*node;
	t_lexer	*prev;

	node = *lst;
	prev = NULL;
	while (node)
	{
		if (!is_word_token(node->token))
			advance_nodes(&prev, &node);
		else if (check_variable(node, envp))
			return (1);
		else if (node->token == T_INFILE || node->token == T_OUTFILE)
		{
			if (handle_redir(&prev, &node))
				return (1);
		}
		else
		{
			if (node->kind == T_PLAIN && split_plain_node(&node))
				return (1);
			if (!handle_plain_word(lst, &prev, &node))
				advance_nodes(&prev, &node);
		}
	}
	return (0);
}
