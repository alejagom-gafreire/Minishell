/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:49:09 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/31 10:33:21 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cambiar el exit por un error
*/
int	check_simple_quotes(char *line, int pos)
{
	int	i;

	i = pos + 1;
	while (line[i] != '\0' && line[i] != '\'')
	{
		i++;
	}
	// if (line[i] == '\0')
	// {
	// 	printf("ERROR\n");
	// 	exit(1);
	// }
	if (line[i] == '\0')
	{
		printf("Error: command not valid");
		return (-1);
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
		printf("Error: command not valid");
		return (-1);
	}
	printf("\n");
	return (i);
}
