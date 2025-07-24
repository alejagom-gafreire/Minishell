/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madird.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:30:17 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/21 01:52:43 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*a;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	a = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!a)
		return (0);
	ft_strlcpy(a, s1 + start, end - start + 1);
	return (a);
}

/*
int	main(void)
{
	char s1[] = " ----hola mundo!---";
	char set[] = " -";
	char *resultado;

	printf("cadena original: '%s'\n", s1);
	resultado = ft_strtrim(s1, set);
	if (resultado)
	{
		printf("cadena recortada: '%s'\n", resultado);
		free(resultado);
	}
	char s2[] = "***hola***";
	char set2[] = "*";

	printf("cadena original: '%s'\n", s2);
	resultado = ft_strtrim(s2, set2);
	if (resultado)
	{
		printf("cadena recortada: '%s'\n", resultado);
		free(resultado);
	}
	return (0);
}
*/
