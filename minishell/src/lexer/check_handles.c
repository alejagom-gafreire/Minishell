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

static t_lexer	*lexer_last(t_lexer *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

char	*buf_append(char *s, char c)
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

static int	get_buffer(char *line, t_handle *hd, int i)
{
	while (line[i])
	{
		hd->c = line[i];
		if (check_marks(hd, hd->c))
		{
			i++;
			continue ;
		}
		if (!hd->in_sq && !hd->in_dq && is_sep(hd->c))
			break ;
		if (appened_char_buf(hd, hd->c) < 0)
			return (-2);
		i++;
	}
	if (hd->in_sq || hd->in_dq)
		return (free(hd->buf), -1);
	if (!hd->buf)
	{
		hd->buf = ft_strdup("");
		if (!hd->buf)
			return (-2);
	}
	return (i);
}

int	handle_word(char *line, int i, t_lexer **lexer_list, int *first_word)
{
	t_handle	handle;
	t_tokens	type;
	t_kind		kind;
	t_lexer		*last;

	init_handles(&handle);
	i = get_buffer(line, &handle, i);
	if (i < 0)
		return (i);
	last = lexer_last(*lexer_list);
	type = get_token_type(last, first_word, handle.buf);
	kind = get_token_kind(&handle);
	add_token(lexer_list, handle.buf, type, kind);
	free(handle.buf);
	if (type == T_NAME_CMD)
		*first_word = 0;
	return (i);
}
