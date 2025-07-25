/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 23:09:59 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/25 12:51:02 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_redirect(char *line, int i, t_lexer **lexer_list,
		int *last_token)
{
	if (line[i + 1] == '<')
	{
		add_token(lexer_list, "<<", T_REDIR_IN);
		*last_token = T_REDIR_IN;
		return (i + 2);
	}
	add_token(lexer_list, "<", T_REDIR_IN);
	*last_token = T_REDIR_IN;
	return (i + 1);
}

int	handle_output_redirect(char *line, int i, t_lexer **lexer_list,
		int *last_token)
{
	if (line[i + 1] == '>')
	{
		add_token(lexer_list, ">>", T_REDIR_OUT);
		*last_token = T_REDIR_OUT;
		return (i + 2);
	}
	add_token(lexer_list, ">", T_REDIR_OUT);
	*last_token = T_REDIR_OUT;
	return (i + 1);
}

int	handle_simple_quotes(char *line, int i, t_lexer **lexer_list)
{
	int		end;
	char	*word;

	end = check_simple_quotes(line, i);
	word = ft_substr(line, i + 1, end - (i + 1));
	add_token(lexer_list, word, T_GENERAL);
	free(word);
	return (end + 1);
}

int	handle_double_quotes(char *line, int i, t_lexer **lexer_list)
{
	int		end;
	char	*word;

	end = check_double_quotes(line, i);
	word = ft_substr(line, i + 1, end - (i + 1));
	add_token(lexer_list, word, T_GENERAL);
	free(word);
	return (end + 1);
}

int	handle_word(char *line, int i, t_lexer **lexer_list, int *last_token,
		int *first_word)
{
	int		start;
	char	*word;

	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>'
		&& line[i] != '|')
		i++;
	word = ft_substr(line, start, i - start);
	if (*last_token == T_REDIR_IN)
	{
		add_token(lexer_list, word, T_INFILE);
		*last_token = T_INFILE;
	}
	else if (*last_token == T_REDIR_OUT)
	{
		add_token(lexer_list, word, T_OUTFILE);
		*last_token = T_OUTFILE;
	}
	else
	{
		add_token(lexer_list, word, T_NAME_CMD);
		*last_token = T_NAME_CMD;
	}
	*first_word = 0;
	free(word);
	return (i);
}
