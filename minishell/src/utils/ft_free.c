/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:29:11 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/29 10:37:52 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_lexer(t_lexer *lexer)
{
	t_lexer	*temp;

	while (lexer)
	{
		temp = lexer;
		lexer = lexer->next;
        free(temp->inf);
		free(temp);
	}
}

static void	free_parcer(t_parcer *parcer)
{
	t_parcer	*temp;

	while (parcer)
	{
		temp = parcer;
		if (parcer->cmd_args)
			free(parcer->cmd_args);
		if (parcer->name_infile)
			free(parcer->name_infile);
		if (parcer->name_outfile)
			free(parcer->name_outfile);
		parcer = parcer->next;
		free(temp);
	}
}
void	free_minishell(t_mini *mini)
{
	if (mini != NULL)
	{
		free_lexer(mini->lexer);
		free_parcer(mini->parcer);
		free(mini);
	}
}