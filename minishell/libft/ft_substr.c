/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:36:42 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/24 13:04:34 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;
	size_t	str_len;

	str_len = ft_strlen(s);
	if (start >= str_len)
	{
		substr = (char *)malloc(1);
		if (substr)
			substr[0] = '\0';
		return (substr);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = start;
	j = 0;
	while (j < len && s[i] != '\0')
		substr[j++] = s[i++];
	substr[j] = '\0';
	return (substr);
}

/*
int	main(void)
{
	char	*cadena_original;
	size_t	start;
	size_t	len;
	char	*resultado;

	cadena_original = "hola mundo";
	start = 5;
	len = 6;
	resultado = ft_substr(cadena_original, start, len);
	if (resultado != NULL)
	{
		printf("subcadena: %s\n", resultado);
		free(resultado);
	}
	else
	{
		printf("error al crear la subcadena. \n");
	}
	return (0);
}
*/