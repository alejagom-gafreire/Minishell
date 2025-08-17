/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:00:23 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/30 17:26:35 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*aux_parcer(char *cmd, char *sec)
{
	char	*res;
	char	*temp;

	res = NULL;
	temp = NULL;
	temp = ft_strjoin(cmd, " ");
	free(cmd);
	res = ft_strjoin(temp, sec);
	free(temp);
	return (res);
}

t_lexer		*handle_inflie(t_lexer *aux, t_parcer *new_parcer)
{
	if (!aux)
		return  (NULL);
	new_parcer->name_infile = ft_strdup(aux->inf);
	new_parcer->infile = open(aux->inf, O_RDONLY);
	return (aux->next);
}

t_lexer		*check_heredoc(t_lexer *aux, t_parcer *new_parcer)
{
	if (aux->next)
	{
		new_parcer->infile = read_heredoc(aux->next->inf);
		return (aux->next->next);
	}
	return (aux->next);
}

t_lexer		*handle_outfile(t_lexer *aux, t_parcer *new_parcer)
{
	int	appened;

	if (!aux || !aux->next || aux->next->token != T_OUTFILE)
	{
		if (!aux)
			return (NULL);
		return (aux->next);
	}
	new_parcer->name_outfile = ft_strdup(aux->next->inf);
	appened = (ft_strncmp(aux->inf, ">>", 3) == 0);
	new_parcer->outfile = open_outfile(aux->next->inf, appened);
	return (aux->next->next);
}

t_lexer		*handle_cmd(t_lexer *aux, char **cmd)
{
	if (!aux)
		return (NULL);
	if (!*cmd)
		*cmd = ft_strdup(aux->inf);
	else	
		*cmd = aux_parcer(*cmd, aux->inf);
	return (aux->next);
}
