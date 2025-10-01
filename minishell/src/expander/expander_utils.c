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

/*
	advance_nodes:
	- Helper to iterate through the linked list
*/
void	advance_nodes(t_lexer **prev, t_lexer **node)
{
	*prev = *node;
	*node = (*node)->next;
}
/*
	is_empty_tkn:
	- Indicates if the node's info is empty
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
	- Expands the string in two passes
*/

char	*expand_vars_two_pass(const char *str, t_shell *envp)
{
	size_t	size;
	char	*out;

	if (!str)
		return (ft_strdup(""));
	size = measure_expanded_len(str, envp);
	out = (char *)malloc(size + 1);
	if (!out)
		return (NULL);
	write_expanded(out, str, envp);
	return (out);
}
