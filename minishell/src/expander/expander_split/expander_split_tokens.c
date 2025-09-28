/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-28 15:52:42 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-28 15:52:42 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ¿Es letra o '_'? */
static int	ws_is_name_start(char c)
{
	return ((c == '_') || ft_isalpha((unsigned char)c));
}

/* ¿Es letra, dígito o '_'? */
static int	ws_is_name_char(char c)
{
	return (ws_is_name_start(c) || ft_isalnum((unsigned char)c));
}

/* NAME=VALUE (sin espacios alrededor del '=') → assignment word */
int	ws_is_assignment_word(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || !ws_is_name_start(s[0]))
		return (0);
	while (s[i] && ws_is_name_char(s[i]))
		i++;
	return (s[i] == '=');
}

/* === helpers seguros, no destructivos === */
int	ws_is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
