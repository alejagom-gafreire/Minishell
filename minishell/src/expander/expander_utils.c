/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:41:37 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/14 17:42:45 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ===================== Utils ===================== */

/*
	advance_nodes:
	-	Helper para iterar por la lista enlazada
*/
void	advance_nodes(t_lexer **prev, t_lexer **node)
{
	*prev = *node;
	*node = (*node)->next;
}
/*
	is_empty_tkn:
	- indica si en el nodo la info esta vacía
*/

int	is_empty_tkn(t_lexer *node)
{
	return (!node->inf || node->inf[0] == '\0');
}

void	free_lexer_node(t_lexer *node)
{
	if (!node)
		return ;
	free(node->inf);
	free(node);
}
/*
	expand_vars_two_pass:
	- Expande la cadena en dos pasadas
*/

char	*expand_vars_two_pass(const char *str, int last_status)
{
	size_t	size;
	char	*out;

	if (!str)
		return (ft_strdup(""));
	size = measure_expanded_len(str, last_status);
	out = (char *)malloc(size + 1);
	if (!out)
		return (NULL);
	write_expanded(out, str, last_status);
	return (out);
}
