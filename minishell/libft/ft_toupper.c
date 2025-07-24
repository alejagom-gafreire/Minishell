/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madird.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:10:34 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/21 01:56:49 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		return (c - 32);
	}
	else
	{
		return (c);
	}
}
/*
int	main(void)
{
	char	letra;
	char	letra_mayuscula;

	letra = 'a';
	printf("letra introducida %c\n", letra);
	letra_mayuscula = ft_toupper(letra);
	printf("mayuscula %c\n", letra_mayuscula);
	return (0);
}
*/