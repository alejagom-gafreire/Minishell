/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-19 08:23:34 by gafreire          #+#    #+#             */
/*   Updated: 2025-08-19 08:23:34 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	set_zero:
	writes 0 and '\0'
*/
static void	set_zero(char buf[32])
{
	buf[0] = '0';
	buf[1] = '\0';
}

/*
	init_value:
	initializes the absolute value and sign for the conversion
*/
static void	init_value(long long *value, int *neg, int st)
{
	*value = (long long)st;
	*neg = 0;
	if (*value < 0)
	{
		*neg = 1;
		*value = -(*value);
	}
}

/*
	fill_tmp:
	fills tmp in reverse order
*/
static int	fill_tmp(long long value, int neg, char tmp[32])
{
	int	pos;
	int	digit;

	pos = 0;
	while (value > 0 && pos < 31)
	{
		digit = (int)(value % 10);
		tmp[pos] = (char)('0' + digit);
		pos++;
		value /= 10;
	}
	if (neg && pos < 31)
	{
		tmp[pos] = '-';
		pos++;
	}
	return (pos);
}

/*
	copy_reverse:
	copies tmp reversed into buf and adds '\0'
*/
static void	copy_reverse(const char tmp[32], int pos, char buf[32])
{
	int	i;

	i = 0;
	while (i < pos)
	{
		buf[i] = tmp[pos - 1 - i];
		i++;
	}
	buf[pos] = '\0';
}

/*
	itoa_status:
	Converts an integer status code (st) into a string.
	- Writes the result into buf (must have space for 32 chars).
	- Handles sign and zero correctly.
	- Returns buf as a null-terminated string.
*/

char	*itoa_status(int st, char buf[32])
{
	long long	value;
	int			neg;
	char		tmp[32];
	int			pos;

	if (st == 0)
	{
		set_zero(buf);
		return (buf);
	}
	init_value(&value, &neg, st);
	pos = fill_tmp(value, neg, tmp);
	copy_reverse(tmp, pos, buf);
	return (buf);
}
