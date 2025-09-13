/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-12 11:41:15 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-12 11:41:15 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*handle_infile(t_lexer *aux, t_parcer *new_parcer)
{
	if (!aux)
		return (NULL);
	new_parcer->name_infile = ft_strdup(aux->inf);
	new_parcer->infile = open(aux->inf, O_RDONLY);
	return (aux->next);
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
