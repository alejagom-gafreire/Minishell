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
	if (new_parcer->infile == -1)
	{
		printf("No such file or directory\n");
		new_parcer->syntax_error = 1;
		new_parcer->redir_error = 1;
		return (aux->next);
	}
	return (aux->next);
}

t_lexer	*handle_outfile(t_lexer *aux, t_parcer *new_parcer, t_shell **env, t_mini *mini)
{
	int	appened;

	if (!aux)
		return (NULL);
	if (new_parcer->redir_error || (*env)->error_heredoc != 0)
	{
		if (aux->next == NULL)
			return (NULL);
		return (aux->next->next);
	}
	if (!aux || !aux->next || aux->next->token != T_OUTFILE)
		return (aux->next);
	appened = (ft_strncmp(aux->inf, ">>", 3) == 0);
	new_parcer->outfile = open_outfile(aux->next->inf, appened, env);
	if (new_parcer->outfile == -1)
	{
		if ((*env)->denied_open != 0)
		{
			printf("Permission denied\n");
			(*env)->denied_open = 0;
		}
		else
			printf("No such file or directory\n");
		(*env)->error_redirect = 1;
		(void)mini;
		// mini->num_cmd = 0;
	}
	return (aux->next->next);
}
