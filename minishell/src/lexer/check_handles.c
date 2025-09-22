/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_handles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 23:09:59 by alejogogi         #+#    #+#             */
/*   Updated: 2025/08/12 10:48:17 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *line, int i, t_lexer **lexer_list,int *first_word)
{
	if (line[i] == '\'')
		i = handle_simple_quotes(line, i, lexer_list,first_word);
	else if (line[i] == '"')
		i = handle_double_quotes(line, i, lexer_list,first_word);
	return (i);
}

int	handle_simple_quotes(char *line, int i, t_lexer **lexer_list,int *first_word)
{
	int		end;
	char	*word;
	t_tokens	type;

	end = check_simple_quotes(line, i);
	if (end < 0)
		return (-1);
	word = ft_substr(line, i + 1, end - (i + 1));
	// Decide el type según contexto/redirecciones/primer word
	if (*lexer_list && (*lexer_list)->last_token == T_REDIR_IN)
		type = T_INFILE;
	else if (*lexer_list && (*lexer_list)->last_token == T_REDIR_OUT)
		type = T_OUTFILE;
	else if (*lexer_list && (*lexer_list)->last_token == T_HEREDOC)
		type = T_DELIM;
	else if (*first_word)
		type = compare_builtins(word);     // ← CLAVE
	else
		type = T_GENERAL;

	add_token(lexer_list, word, type, T_SQ);
	(*lexer_list)->last_token = type;
	if (type == T_NAME_CMD)
		*first_word = 0;
	free(word);
	return (end + 1);
}

int	handle_double_quotes(char *line, int i, t_lexer **lexer_list,int *first_word)
{
	int		end;
	char	*word;
	t_tokens	type;

	end = check_double_quotes(line, i);
	if (end < 0)
		return (-1);
	word = ft_substr(line, i + 1, end - (i + 1));
	if (*lexer_list && (*lexer_list)->last_token == T_REDIR_IN)
		type = T_INFILE;
	else if (*lexer_list && (*lexer_list)->last_token == T_REDIR_OUT)
		type = T_OUTFILE;
	else if (*lexer_list && (*lexer_list)->last_token == T_HEREDOC)
		type = T_DELIM;
	else if (*first_word)
		type = compare_builtins(word);     // ← CLAVE
	else
		type = T_GENERAL;
	
	add_token(lexer_list, word, type, T_DQ);
	(*lexer_list)->last_token = type;
	if (type == T_NAME_CMD)
		*first_word = 0;
	free(word);
	return (end + 1);
}

void	check_tkn(t_lexer **lexer_list, char *word, t_tokens *type,
		t_kind *kind, int *first_word)
{
	*kind = T_PLAIN;
	if (*lexer_list && (*lexer_list)->last_token == T_REDIR_IN)
	{
		*type = T_INFILE;
	}
	else if (*lexer_list && (*lexer_list)->last_token == T_REDIR_OUT)
	{
		*type = T_OUTFILE;
	}
	else if (*lexer_list && (*lexer_list)->last_token == T_HEREDOC)
	{
		*type = T_DELIM;
	}
	else if (*first_word)
	{
		*type = compare_builtins(word);
		*first_word = 0;
	}
	// else
	// {
	// 	*type = compare_builtins(word);
	// 	*kind = T_PLAIN;
	// }
}

int	handle_word(char *line, int i, t_lexer **lexer_list, int *first_word)
{
	int			start;
	char		*word;
	t_tokens	type;
	t_kind		kind;

	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>'
		&& line[i] != '|')
		i++;
	word = ft_substr(line, start, i - start);
	if (!word)
		return (-1);
	check_tkn(lexer_list, word, &type, &kind,first_word);
	add_token(lexer_list, word, type, kind);
	(*lexer_list)->last_token = type;
	if (type == T_NAME_CMD)
		*first_word = 0;
	return (free(word), i);
}
