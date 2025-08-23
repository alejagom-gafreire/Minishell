/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-22 11:24:23 by gafreire          #+#    #+#             */
/*   Updated: 2025-08-22 11:24:23 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
===================== Expansión optimizada (dos pasadas) =====================
 Reglas:
   - $?: sustituir por last_status
   - $NAME: NAME = [A-Za-z_][A-Za-z0-9_]* -> getenv(NAME) o "" si no existe
   - $ seguido de char no válido / fin: se trata como '$' literal
   - No field splitting. No ${}, $1, $$,
	etc. (quedan literales salvo $? y $NAME)
*/

/* 
	write_status:
	escribir last_status en dst 
*/
static void	write_status(char *dst, size_t *p, int last_status)
{
	char		buf[32];
	const char	*txt;
	size_t		len;

	txt = itoa_status(last_status, buf);
	len = ft_strlen(txt);
	ft_memcpy(dst + *p, txt, len);
	*p += len;
}

/* 
	handle_simple_write:
	casos simples: normal, '$' final, '$' sin nombre válido 
*/
static int	handle_simple_write(const char *s, size_t *i, char *dst, size_t *p)
{
	if (s[*i] != '$')
	{
		dst[*p] = s[*i];
		(*p)++;
		(*i)++;
		return (1);
	}
	if (s[*i + 1] == '\0')
	{
		dst[*p] = '$';
		(*p)++;
		(*i)++;
		return (1);
	}
	if (!is_var_start(s[*i + 1]))
	{
		dst[*p] = '$';
		(*p)++;
		(*i)++;
		return (1);
	}
	return (0);
}

/*
	write_var_span:
	escribe $NAME (usa getenv); devuelve 1 si OOM, 0 si OK 
*/
static int	write_var_span(const char *s, size_t *i, char *dst, size_t *p)
{
	size_t	st;
	size_t	en;
	size_t	len;
	char	*name;

	st = *i + 1;
	en = scan_var_end(s, st);
	name = (char *)malloc((en - st) + 1);
	if (name == NULL)
		return (1);
	ft_memcpy(name, s + st, en - st);
	name[en - st] = '\0';
	if (getenv(name) != NULL)
		len = ft_strlen(getenv(name));
	else
		len = 0;
	if (len > 0)
	{
		ft_memcpy(dst + *p, getenv(name), len);
		*p += len;
	}
	free(name);
	*i = en;
	return (0);
}

/* 
	write_expanded:
	principal: escribe s expandida en dst 
*/
void	write_expanded(char *dst, const char *s, int last_status)
{
	size_t	i;
	size_t	p;

	i = 0;
	p = 0;
	while (s && s[i])
	{
		if (handle_simple_write(s, &i, dst, &p))
			continue ;
		if (s[i + 1] == '?')
		{
			write_status(dst, &p, last_status);
			i += 2;
			continue ;
		}
		if (write_var_span(s, &i, dst, &p))
			break ;
	}
	dst[p] = '\0';
}
