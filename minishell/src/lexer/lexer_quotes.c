/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:49:09 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/30 20:18:08 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cambiar el exit por un error
*/

void	num_comands(t_mini *mini)
{
	int			i;
	t_parcer	*list;
	
	mini->exec = malloc(sizeof(t_execute));
	if (!mini->exec)
		exit(EXIT_FAILURE);
	i = 0;
	list = mini->parcer;
	while (list)
	{
		i++;
		list = list->next;
	}
	mini->exec->cmds = i;
}

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
