/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-28 15:51:35 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-28 15:51:35 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates a simple word node (GENERAL, PLAIN) without modifying anything else */
t_lexer	*ws_new_field(const char *s, size_t len)
{
	t_lexer	*n;

	n = (t_lexer *)malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->inf = ft_substr(s, 0, (int)len);
	if (!n->inf)
	{
		free(n);
		return (NULL);
	}
	n->token = T_GENERAL;
	n->kind = T_PLAIN;
	n->next = NULL;
	n->last = NULL;
	return (n);
}

/* Inserts 'n' immediately AFTER 'pos' in the doubly linked list. */

void	ws_insert_after(t_lexer *pos, t_lexer *n)
{
	if (!pos || !n)
		return ;
	n->last = pos;
	n->next = pos->next;
	if (pos->next)
		pos->next->last = n;
	pos->next = n;
}

void	ws_normalize_plain_node(t_lexer *cur)
{
	cur->kind = T_PLAIN;
	if (cur->token == T_NAME_CMD)
		cur->token = T_GENERAL;
}
