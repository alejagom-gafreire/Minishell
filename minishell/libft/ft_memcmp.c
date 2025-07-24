/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madird.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:01:28 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/21 01:42:09 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
		{
			return (p1[i] - p2[i]);
		}
		i++;
	}
	return (0);
}

/*
int	main(void)
{
	const char	*str1;
	const char	*str2;
	int			result;
	size_t		n;

	str1 = "Hola mundo";
	str2 = "Hola mundo";
	n = 10;
	result = ft_memcmp(str1, str2, n);
	if (result < 0)
	{
		printf("'%s' es menor que '%s'\n", str1, str2);
	}
	else if (result > 0)
	{
		printf("'%s' es mayor que '%s'\n", str1, str2);
	}
	else
	{
		printf("'%s' es igual a '%s'\n", str1, str2);
	}
	return (0);
}
*/