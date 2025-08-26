/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-19 10:56:57 by gafreire          #+#    #+#             */
/*   Updated: 2025-08-19 10:56:57 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ===================== Reconocimiento =====================
	Chequeo que token es
*/
int	is_word_token(int t)
{
	return (t == T_NAME_CMD || t == T_GENERAL || t == T_INFILE
		|| t == T_OUTFILE);
}

int	is_var_start(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

int	is_var_char(char c)
{
	return (is_var_start(c) || (c >= '0' && c <= '9'));
}
