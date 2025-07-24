/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madird.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:42:43 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/21 01:42:00 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	size_t				i;

	ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
		{
			return ((void *)(ptr + i));
		}
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	const char	*texto;
	char		letra;
	char		*resultado;

	texto = "Buenas mundo de la Pogramacion";
	letra = 's';
	resultado = ft_memchr(texto, letra, strlen(texto));
	if (resultado != NULL)
	{
		printf("la letra '%c'posicion: %ld\n", letra, resultado - texto);
	}
	else
	{
		printf("la letra '%c' no se encontro en el texto. \n", letra);
	}
	return (0);
}
*/