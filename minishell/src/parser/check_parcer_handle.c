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

t_lexer	*handle_inflie(t_lexer *aux, t_parcer *new_parcer)
{
	if (!aux)
		return (NULL);
	new_parcer->name_infile = ft_strdup(aux->inf);
	new_parcer->infile = open(aux->inf, O_RDONLY);
	return (aux->next);
}

t_lexer	*check_heredoc(t_lexer *aux, t_parcer *new_parcer)
{
	if (aux->next && aux->next->token == T_DELIM)
	{
		new_parcer->infile = read_heredoc(aux->next->inf);
		return (aux->next->next);
	}
	else
	{
		printf("syntax error near unexpected token '%s'\n", aux->next->inf);
		new_parcer->syntax_error = 1;
		return (NULL);
	}
}

t_lexer	*handle_outfile(t_lexer *aux, t_parcer *new_parcer)
{
	int	appened;

	if (!aux || !aux->next || aux->next->token != T_OUTFILE)
	{
		if (!aux)
			return (NULL);
		return (aux->next);
	}
	appened = (ft_strncmp(aux->inf, ">>", 3) == 0);
	new_parcer->outfile = open_outfile(aux->next->inf, appened);
	return (aux->next->next);
}

t_lexer	*handle_cmd(t_lexer *aux, char **cmd)
{
	if (!aux)
		return (NULL);
	if (!*cmd)
		*cmd = ft_strdup(aux->inf);
	else
		*cmd = aux_parcer(*cmd, aux->inf);
	return (aux->next);
}

t_lexer	*check_buildings(t_lexer *aux, t_parcer *new_parcer)
{
	if (!aux)
		return (NULL);
	new_parcer->building = ft_strdup(aux->inf);
	if (!new_parcer->building)
		return (NULL);
	return (aux->next);
}
