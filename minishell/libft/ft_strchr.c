/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:38:14 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/23 05:18:45 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

/*
int	main(void)
{
	char	*string;
	char	buscar;
	char	*resultado;

	string = "buenas Mundo";
	buscar = 'z';
	resultado = ft_strchr(string, buscar);
	if (resultado != 0)
	{
		printf("caracter '%c' encontrado %s\n", buscar, resultado);
	}
	else
	{
		printf("caracter no encontrado '%c'\n", buscar);
	}
	return (0);
}
*/