/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-28 15:44:51 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-28 15:44:51 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	check_variable:
	- Chequea si el contenido requiere expansión
*/
int	check_variable(t_lexer *node, t_shell *envp)
{
	char	*expand;

	if (node->kind != T_DQ && node->kind != T_PLAIN)
		return (0);
	expand = expand_vars_two_pass(node->inf, envp);
	if (!expand)
		return (1);
	free(node->inf);
	node->inf = expand;
	return (0);
}
