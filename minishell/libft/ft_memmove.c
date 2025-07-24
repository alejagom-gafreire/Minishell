/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:57:04 by alejagom          #+#    #+#             */
/*   Updated: 2024/10/23 04:19:44 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	ptr_dst = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	if (!dest && !src && n > 0)
		return (NULL);
	else if (ptr_dst > ptr_src)
	{
		while (n--)
			ptr_dst[n] = ptr_src[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

/*
int	main(void)
{
	char	str[20] = "hola, mundo";

	printf("primero %s\n", str);
	ft_memmove(str + 6, str, 5);
	printf("segundo %s\n", str);
	return (0);
}
*/
