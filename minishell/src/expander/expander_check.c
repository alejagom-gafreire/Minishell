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
	1st pass: measure final length
*/

char	*get_env(char *name, char **envp)
{
	size_t	name_len;
	int		i;
	char	*cpy;
	size_t	key_len;

	if (!name || !envp)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		cpy = ft_strchr(envp[i], '=');
		if (cpy)
		{
			key_len = (size_t)(cpy - envp[i]);
			if (key_len == name_len && ft_strncmp(envp[i], name, name_len) == 0)
				return (cpy + 1);
		}
		i++;
	}
	return (NULL);
}

static size_t	len_of_status(int st)
{
	char		buf[32];
	const char	*s;
	size_t		len;

	s = itoa_status(st, buf);
	len = ft_strlen(s);
	return (len);
}

/*
	env_len_span:
	get the length of the variable's value without allocating
*/

static size_t	env_len_span(const char *s, size_t st, size_t en, t_shell *envp)
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
	val = get_env(name, envp->envi);
	if (val != NULL)
		l = ft_strlen(val);
	else
		l = 0;
	free(name);
	return (l);
}

/*
	handle_simple_cases:
	Consume simple cases: no '$', trailing '$', or '$?'.
	Returns 1 if it consumed something and advanced; 0 if not.
*/

static int	handle_simple_cases(const char *s, size_t *i, size_t *out,
		t_shell *envp)
{
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
	if (s[*i + 1] == '?')
	{
		(*out) += len_of_status(envp->last_status);
		(*i) += 2;
		return (1);
	}
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
	Gets the exact final length after checking quoting
	and expansion rules.
*/

size_t	measure_expanded_len(const char *s, t_shell *envp)
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
		if (handle_simple_cases(s, &i, &out, envp))
			continue ;
		en = scan_var_end(s, i + 1);
		out += env_len_span(s, i + 1, en, envp);
		i = en;
	}
	return (out);
}
