/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madird.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:15:01 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/21 01:52:02 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	const char	*last;
	char		a;

	a = (char)c;
	last = NULL;
	while (*str != '\0')
	{
		if (*str == a)
		{
			last = str;
		}
		str++;
	}
	if (a == '\0')
	{
		return ((char *)str);
	}
	return ((char *)last);
}

/*
int	main(void)
{
	char	*string;
	char	buscar;
	char	*resultado;

	string = "Holla Mundo de 42";
	buscar = 'z';
	resultado = ft_strrchr(string, buscar);
	if (resultado != NULL)
	{
		printf("ultima aparicion '%c' encontrada: \"%s\"\n", buscar, resultado);
	}
	else
	{
		printf("caracter '%c' no encontrado \n", buscar);
	}
	return (0);
}
*/