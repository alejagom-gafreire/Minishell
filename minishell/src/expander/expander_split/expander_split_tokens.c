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

/* Is it a letter or '_'? */
static int	ws_is_name_start(char c)
{
	return ((c == '_') || ft_isalpha((unsigned char)c));
}

/* Is it a letter, digit, or '_'? */
static int	ws_is_name_char(char c)
{
	return (ws_is_name_start(c) || ft_isalnum((unsigned char)c));
}

/* NAME=VALUE (no spaces around '=') → assignment word */
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

int	ws_is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
