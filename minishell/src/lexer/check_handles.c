/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_handles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 23:09:59 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/30 11:41:08 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *line, int i, t_lexer **lexer_list)
{
	if (line[i] == '\'')
		i = handle_simple_quotes(line, i, lexer_list);
	else if (line[i] == '"')
		i = handle_double_quotes(line, i, lexer_list);
	return (i);
}

int	handle_simple_quotes(char *line, int i, t_lexer **lexer_list)
{
	int		end;
	char	*word;

	end = check_simple_quotes(line, i);
	if (end < 0)
		return (-1);
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
	if (end < 0)
		return (-1);
	word = ft_substr(line, i + 1, end - (i + 1));
	add_token(lexer_list, word, T_GENERAL);
	free(word);
	return (end + 1);
}

t_tokens	compare_buildings(char *word)
{
	t_tokens	type;

	if (ft_strcmp("cd", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("echo", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("pwd", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("export", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("unset", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("env", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("exit", word) == 0)
		type = T_BUILDINGS;
	else
		type = T_NAME_CMD;
	return (type);
}

int	handle_word(char *line, int i, t_lexer **lexer_list, int *first_word)
{
	int			start;
	char		*word;
	t_tokens	type;

	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>'
		&& line[i] != '|')
		i++;
	word = ft_substr(line, start, i - start);
	if (!word)
		return (-1);
	if (*lexer_list && (*lexer_list)->last_token == T_REDIR_IN)
		type = T_INFILE;
	else if (*lexer_list && (*lexer_list)->last_token == T_REDIR_OUT)
		type = T_OUTFILE;
	else if (*lexer_list && (*lexer_list)->last_token == T_HEREDOC)
		type = T_DELIM;
	else 
		type = compare_buildings(word);
	add_token(lexer_list, word, type);
	(*lexer_list)->last_token = type;
	if (type == T_NAME_CMD)
		*first_word = 0;
	return (free(word), i);
}
