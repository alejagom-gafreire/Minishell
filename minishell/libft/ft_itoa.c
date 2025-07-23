/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:16:13 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/24 16:23:02 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	num = n;
	len = ft_intlen(num);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	if (n == 0)
		str[0] = '0';
	return (str);
}
/*
int	main(void)
{
	int		numeros[] = {123, -456, 0, -2147483648, 2147483647};
	size_t	total_numeros;
	char	*resultado;

	total_numeros = sizeof(numeros) / sizeof(numeros[0]);
	for (size_t i = 0; i < total_numeros; i++)
	{
		resultado = ft_itoa(numeros[i]);
		if (!resultado)
		{
			printf("Error en la conversión de %d\n", numeros[i]);
			return (1);
		}
		printf("Número %d convertido a cadena: %s\n", numeros[i], resultado);
		free(resultado);
	}
	return (0);
}
*/