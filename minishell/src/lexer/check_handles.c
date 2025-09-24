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

static int	is_sep(char c)
{
	return (c == ' ' || c == '|' || c == '<' || c == '>');
}

static char	*buf_append(char *s, char c)
{
	size_t	len;
	char	*wrd;

	len = 0;
	if (s)
		len = ft_strlen(s);
	wrd = (char *)malloc(len + 2);
	if (!wrd)
		return (free(s), NULL);
	if (s)
	{
		ft_memcpy(wrd, s, len);
		free(s);
	}
	wrd[len] = c;
	wrd[len + 1] = '\0';
	return (wrd);
}

static t_lexer	*lexer_last(t_lexer *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	handle_word(char *line, int i, t_lexer **lexer_list, int *first_word)
{
	int			in_sq;
	int			in_dq;
	int			had_plain;
	int			had_sq;
	int			had_dq;
	char		*buf;
	char		c;
	t_tokens	type;
	t_kind		kind;
	t_lexer		*last;

	in_sq = 0;
	in_dq = 0;
	had_plain = 0;
	had_sq = 0;
	had_dq = 0;
	buf = NULL;
	while (line[i])
	{
		c = line[i];
		if (c == '\'' && !in_dq)
		{
			in_sq = !in_sq;
			i++;
			continue ;
		}
		if (c == '"' && !in_sq)
		{
			in_dq = !in_dq;
			i++;
			continue ;
		}
		if (!in_sq && !in_dq && is_sep(c))
			break ;
		buf = buf_append(buf, c);
		if (!buf)
			return (-2);
		if (in_sq)
			had_sq = 1;
		else if (in_dq)
			had_dq = 1;
		else
			had_plain = 1;
		i++;
	}
	if (in_sq || in_dq)
		return (free(buf), -1);
	if (!buf)
	{
		buf = ft_strdup("");
		if (!buf)
			return (-2);
	}
	last = lexer_last(*lexer_list);
	if (last && last->token == T_REDIR_IN)
		type = T_INFILE;
	else if (last && last->token == T_REDIR_OUT)
		type = T_OUTFILE;
	else if (last && last->token == T_HEREDOC)
		type = T_DELIM;
	else if (*first_word)
		type = compare_builtins(buf);
	else
		type = T_GENERAL;
	if (had_sq && !had_dq && !had_plain)
		kind = T_SQ;
	else if (had_dq && !had_sq && !had_plain)
		kind = T_DQ;
	else
		kind = T_PLAIN;
	add_token(lexer_list, buf, type, kind);
	free(buf);
	if (type == T_NAME_CMD)
		*first_word = 0;
	return (i);
}
