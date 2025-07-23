/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:57:30 by alejagom          #+#    #+#             */
/*   Updated: 2024/10/23 04:27:08 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	a = dst_len;
	b = 0;
	if (size <= dst_len)
		return (size + src_len);
	while (src[b] && a < size - 1)
	{
		dst[a++] = src[b++];
	}
	dst[a] = '\0';
	return (dst_len + src_len);
}

/*
int	main(void)
{
	char		dest[20] = "Holla";
	const char	*src = " mundo";
	size_t		final;

	printf("primera: %s\n", dest);
	final = ft_strlcat(dest, src, sizeof(dest));
	printf("despues: %s\n", dest);
	printf("long: %zu\n", final);
	return (0);
}
*/