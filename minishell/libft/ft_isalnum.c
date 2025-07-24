/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madird.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:37 by alejagom          #+#    #+#             */
/*   Updated: 2024/10/21 01:38:46 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
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

	if (ft_isalnum(i))
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