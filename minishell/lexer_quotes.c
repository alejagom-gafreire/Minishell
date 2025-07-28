/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:49:09 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/28 09:18:55 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	// cambiar salida por error
*/
int	check_simple_quotes(char *line, int pos)
{
	int	i;

	i = pos + 1;
	while (line[i] != '\0' && line[i] != '\'')
	{
		i++;
	}
	if (line[i] == '\0')
	{
		printf("ERROR\n");
		exit(1);
	}
	printf("\n");
	return (i);
}

int	check_double_quotes(char *line, int pos)
{
	int	i;

	i = pos + 1;
	while (line[i] != '\0' && line[i] != '"')
	{
		i++;
	}
	if (line[i] == '\0')
	{
		printf("ERROR\n");
		exit(1);
	}
	printf("\n");
	return (i);
}
