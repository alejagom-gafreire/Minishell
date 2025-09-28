/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-28 15:42:35 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-28 15:42:35 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Hace word-splitting SOLO si:
 *   - node->kind == T_PLAIN
 *   - node->token es palabra normal (T_NAME_CMD o T_GENERAL)
 * No borra el nodo actual. Si la expansión queda vacía o solo IFS, deja el nodo
 * con cadena vacía "" (así no reventamos punteros); ya decidirás más tarde si
 * ese token vacío se descarta en tu pipeline de construcción de argv.
 */

// --- helpers ---

static int	ws_should_split(t_lexer *cur)
{
	if (!cur)
		return (0);
	if (cur->kind != T_PLAIN)
		return (0);
	if (!(cur->token == T_GENERAL || cur->token == T_NAME_CMD))
		return (0);
	if (!cur->inf || ws_is_assignment_word(cur->inf))
		return (0);
	return (1);
}

static int	ws_set_empty_plain(t_lexer *cur, char *orig, char *copy)
{
	char	*empty;

	empty = ft_strdup("");
	if (!empty)
		return (free(copy), 1);
	cur->inf = empty;
	ws_normalize_plain_node(cur);
	return (free(orig), free(copy), 0);
}

static char	*ws_dup_span(char **pp)
{
	char	*start;
	char	*p;

	start = *pp;
	p = *pp;
	while (*p && !ws_is_ifs(*p))
		p++;
	*pp = p;
	return (ft_substr(start, 0, (int)(p - start)));
}

static int	ws_append_field(char **pp, t_lexer **plast)
{
	t_lexer	*n;
	char	*start;
	char	*p;

	while (**pp && ws_is_ifs(**pp))
		(*pp)++;
	if (!**pp)
		return (0);
	start = *pp;
	p = *pp;
	while (*p && !ws_is_ifs(*p))
		p++;
	n = ws_new_field(start, (size_t)(p - start));
	if (!n)
		return (1);
	ws_insert_after(*plast, n);
	*plast = n;
	*pp = p;
	return (0);
}

// --- función principal (≤25 líneas) ---

int	split_plain_node(t_lexer **pnode)
{
	t_split_state	state;
	char			*field;

	if (!ws_should_split(*pnode))
		return (0);
	state.copy = ft_strdup((*pnode)->inf);
	if (!state.copy)
		return (1);
	state.p = state.copy;
	while (*state.p && ws_is_ifs(*state.p))
		state.p++;
	if (!*state.p)
		return (ws_set_empty_plain(*pnode, (*pnode)->inf, state.copy));
	field = ws_dup_span(&state.p);
	if (!field)
		return (free(state.copy), 1);
	free((*pnode)->inf);
	(*pnode)->inf = field;
	ws_normalize_plain_node(*pnode);
	state.last = *pnode;
	while (*state.p)
		if (ws_append_field(&state.p, &state.last))
			return (free(state.copy), 1);
	*pnode = state.last;
	return (free(state.copy), 0);
}
