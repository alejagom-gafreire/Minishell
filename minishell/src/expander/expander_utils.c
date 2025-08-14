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
char	*dup_cstr(const char *s)
{
	size_t	L;
	char	*p;

	L = 0;
	if (!s)
		return (NULL);
	while (s[L])
		L++;
	p = (char *)malloc(L + 1);
	if (!p)
		return (NULL);
	for (size_t i = 0; i <= L; ++i)
		p[i] = s[i];
	return (p);
}

/* $?: itoa simple a buffer proporcionado */
char	*itoa_status(int st, char buf[32])
{
	unsigned int	n;
	int				i = 0, j = 0, neg;
	char			tmp[32];

	i = 0, j = 0, neg = (st < 0);
	if (st == 0)
	{
		buf[0] = '0';
		buf[1] = '\0';
		return (buf);
	}
	n = neg ? (unsigned int)(-st) : (unsigned int)st;
	while (n > 0 && i < (int)sizeof(tmp))
	{
		tmp[i++] = (char)('0' + (n % 10));
		n /= 10;
	}
	if (neg)
		tmp[i++] = '-';
	while (i--)
		buf[j++] = tmp[i];
	buf[j] = '\0';
	return (buf);
}
