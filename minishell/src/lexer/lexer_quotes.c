/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:49:09 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/06 16:56:18 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	num_comands(t_mini *mini, t_shell *envp)
{
	int			i;
	t_parcer	*list;

	i = 0;
	mini->num_cmd = 0;
	list = mini->parcer;
	while (list)
	{
		if ((list->argv && list->argv[0]) || list->infile != -1
			|| list->outfile != -1)
			i++;
		list = list->next;
	}
	if (envp->error_heredoc != 0 || envp->error_redirect)
	{
		envp->error_heredoc = 0;
		mini->num_cmd = 0;
		return ;
	}
	mini->num_cmd = i;
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
		printf("Error: command not valid\n");
		return (-1);
	}
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
		printf("Error: command not valid\n");
		return (-1);
	}
	return (i);
}
