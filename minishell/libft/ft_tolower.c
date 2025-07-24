/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madird.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:30:41 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/21 01:55:55 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		return (c + 32);
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

	letra = 'M';
	printf("letra introducida %c\n", letra);
	letra_mayuscula = ft_tolower(letra);
	printf("mayuscula %c\n", letra_mayuscula);
	return (0);
}
*/