/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madird.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:32:04 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/21 01:49:14 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*resultado;
	size_t	str1;
	size_t	str2;
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	str1 = ft_strlen(s1);
	str2 = ft_strlen(s2);
	resultado = (char *)malloc((str1 + str2 + 1) * sizeof(char));
	if (resultado == NULL)
		return (NULL);
	while (i < str1)
	{
		resultado[i] = s1[i];
		i++;
	}
	while (a < str2)
	{
		resultado[i + a] = s2[a];
		a++;
	}
	resultado[i + a] = '\0';
	return (resultado);
}

/*
int	main(void)
{
	const char	*str1 = "holla ";
	const char	*str2 = "mundo";
	char		*resultado;

	resultado = ft_strjoin(str1, str2);
	if (resultado != NULL)
	{
		printf("resultado: %s\n", resultado);
		free(resultado);
	}
	else
	{
		printf("error al unir cadenas. \n");
	}
	return(0);
}
*/