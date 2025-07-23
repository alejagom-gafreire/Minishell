/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madird.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:55:24 by alejagom          #+#    #+#             */
/*   Updated: 2024/10/03 16:50:07 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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

	if (ft_isprint(i))
	{
		printf("1: \n", i);
	}
	else
	{
		printf("0: \n", i);
	}
	return(0);
}
*/