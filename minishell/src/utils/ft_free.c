/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:29:11 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/06 16:57:16 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
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

void	free_argv(t_parcer *cmd)
{
	int	i;

	if (!cmd || !cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i])
		free(cmd->argv[i++]);
	free(cmd->argv);
	cmd->argv = NULL;
	cmd->argc = 0;
}

void	free_parcer(t_parcer *parcer)
{
	t_parcer	*temp;

	while (parcer)
	{
		temp = parcer;
		if (parcer->cmd_args)
			free(parcer->cmd_args);
		if (parcer->arg_export)
			free(parcer->arg_export);
		if (parcer->name_infile)
			free(parcer->name_infile);
		if (parcer->name_outfile)
			free(parcer->name_outfile);
		if (parcer->builtin)
			free(parcer->builtin);
		if (parcer->argv)
			free_split(parcer->argv);
		parcer = parcer->next;
		free(temp);
	}
	free_argv(parcer);
}

void	free_minishell(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->lexer)
		free_lexer(mini->lexer);
	if (mini->parcer)
		free_parcer(mini->parcer);
	free(mini);
}

void	free_shell(t_shell *envi)
{
	if (!envi)
		return ;
	if (envi->envi)
		free_split(envi->envi);
}
