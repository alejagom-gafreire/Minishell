/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:11:26 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/12 10:51:10 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(char *line, int i, t_lexer **lexer_list, int *first_word)
{
	if (line[i] == '|')
	{
		handle_pipe(lexer_list, first_word);
		return (i + 1);
	}
	else if (line[i] == '<')
		i = handle_input_redirect(line, i, lexer_list);
	else if (line[i] == '>')
		i = handle_output_redirect(line, i, lexer_list);
	return (i);
}

int	handle_input_redirect(char *line, int i, t_lexer **lexer_list)
{
	if (line[i + 1] == '<')
	{
		add_token(lexer_list, "<<", T_HEREDOC, T_PLAIN);
		(*lexer_list)->last_token = T_HEREDOC;
		return (i + 2);
	}
	add_token(lexer_list, "<", T_REDIR_IN, T_PLAIN);
	(*lexer_list)->last_token = T_REDIR_IN;
	return (i + 1);
}

int	handle_output_redirect(char *line, int i, t_lexer **lexer_list)
{
	if (line[i + 1] == '>')
	{
		add_token(lexer_list, ">>", T_REDIR_OUT, T_PLAIN);
		(*lexer_list)->last_token = T_REDIR_OUT;
		return (i + 2);
	}
	add_token(lexer_list, ">", T_REDIR_OUT, T_PLAIN);
	(*lexer_list)->last_token = T_REDIR_OUT;
	return (i + 1);
}
