/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-22 11:24:06 by gafreire          #+#    #+#             */
/*   Updated: 2025-08-22 11:24:06 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	len_of_status:
	1ª pasada: medir longitud final 
*/

// static size_t	len_of_status(int st)
// {
// 	char		buf[32];
// 	const char	*s;
// 	size_t		len;

// 	s = itoa_status(st, buf);
// 	len = ft_strlen(s);
// 	return (len);
// }
/*
	scan_var_end:
	fin de nombre de variable
*/

size_t	scan_var_end(const char *s, size_t start)
{
	size_t	en;

	en = start;
	while (s[en] && is_var_char(s[en]))
		en++;
	return (en);
}

/*
	env_len_span:
	obtener longitud del valor de la variable sin alocar
*/
static size_t	env_len_span(const char *s, size_t st, size_t en)
{
	size_t		n;
	size_t		i;
	char		*name;
	const char	*val;
	size_t		l;

	n = en - st;
	name = (char *)malloc(n + 1);
	if (name == NULL)
		return (0);
	i = 0;
	while (i < n)
	{
		name[i] = s[st + i];
		i++;
	}
	name[n] = '\0';
	val = getenv(name);
	if (val != NULL)
		l = ft_strlen(val);
	else
		l = 0;
	free(name);
	return (l);
}

/*
	handle_simple_cases:
	Consume casos simples: no '$', '$' final, o '$?'.
   	Devuelve 1 si consumió algo y avanzó; 0 si no. 
*/

static int	handle_simple_cases(const char *s, size_t *i, size_t *out,
		int last_status)
{
	(void)last_status;
	if (s[*i] != '$')
	{
		(*out)++;
		(*i)++;
		return (1);
	}
	if (s[*i + 1] == '\0')
	{
		(*out)++;
		(*i)++;
		return (1);
	}
	// if (s[*i + 1] == '?')
	// {
	// 	(*out) += len_of_status(last_status);
	// 	(*i) += 2;
	// 	return (1);
	// }
	if (!is_var_start(s[*i + 1]))
	{
		(*out)++;
		(*i)++;
		return (1);
	}
	return (0);
}

/* 
	measure_expanded_len:
	Obtiene la longitud final exacta despues de chequear las reglas
	de comillas y expansion.
*/

size_t	measure_expanded_len(const char *s, int last_status)
{
	size_t	i;
	size_t	out;
	size_t	en;

	if (s == NULL)
		return (0);
	i = 0;
	out = 0;
	while (s[i] != '\0')
	{
		if (handle_simple_cases(s, &i, &out, last_status))
			continue ;
		en = scan_var_end(s, i + 1);
		out += env_len_span(s, i + 1, en);
		i = en;
	}
	return (out);
}
