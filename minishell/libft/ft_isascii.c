/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:57 by alejagom          #+#    #+#             */
/*   Updated: 2024/10/23 01:34:14 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*
int	main(void)
{
	char	i ='*';

	if (ft_isascii(i))
	{
		printf("el caracter %c alfanumerico. \n", i);
	}
	else
	{
		printf("el caracter %c no es alfanumerico. \n", i);
	}
	return(0);
}
*/