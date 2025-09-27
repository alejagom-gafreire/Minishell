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
static int	write_var_span(const char *s, size_t *i, t_write *wr, t_shell *envp)
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
	if (get_env(name, envp->envi) != NULL)
		len = ft_strlen(get_env(name, envp->envi));
	else
		len = 0;
	if (len > 0)
	{
		ft_memcpy(wr->dts + wr->pos, get_env(name, envp->envi), len);
		wr->pos += len;
	}
	free(name);
	*i = en;
	return (0);
}

/*
	write_expanded:
	principal: escribe s expandida en dst
*/
void	write_expanded(char *dst, const char *s, t_shell *envp)
{
	size_t	i;
	t_write	wr;

	i = 0;
	wr.dts = dst;
	wr.pos = 0;
	while (s && s[i])
	{
		if (s[i + 1] == '?')
		{
			write_status(wr.dts, &wr.pos, envp->last_status);
			i += 2;
			continue ;
		}
		if (handle_simple_write(s, &i, wr.dts, &wr.pos))
			continue ;
		if (write_var_span(s, &i, &wr, envp))
			break ;
	}
	wr.dts[wr.pos] = '\0';
}
