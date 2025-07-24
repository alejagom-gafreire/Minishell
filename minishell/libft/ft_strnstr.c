/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:38:47 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/25 10:26:19 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	a;

	if (!*little)
	{
		return ((char *)big);
	}
	i = 0;
	while (i < n && big[i])
	{
		a = 0;
		while (big[i + a] == little[a] && (i + a) < n)
		{
			if (little[a + 1] == '\0')
			{
				return ((char *)&big[i]);
			}
			a++;
		}
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	const char	*texto;
	const char	*buscar;
	char		*res;
	size_t		i;

	texto = "Holla mundo";
	buscar = "mundo";
	i = 12;
	res = ft_strnstr(texto, buscar, i);
	if (res)
	{
		printf("sub string encontrado: '%s'\n", res);
	}
	else
	{
		printf("sub string no encontrado. \n");
	}
	return (0);
}
*/