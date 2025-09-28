/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:02:54 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/27 12:02:56 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_handles(t_handle *handle)
{
	handle->in_sq = 0;
	handle->in_dq = 0;
	handle->had_plain = 0;
	handle->had_sq = 0;
	handle->had_dq = 0;
	handle->buf = NULL;
}

t_tokens	get_token_type(t_lexer *last, int *first_word, char *buf)
{
	if (last && last->token == T_REDIR_IN)
		return (T_INFILE);
	else if (last && last->token == T_REDIR_OUT)
		return (T_OUTFILE);
	else if (last && last->token == T_HEREDOC)
		return (T_DELIM);
	else if (*first_word)
		return (compare_builtins(buf));
	else
		return (T_GENERAL);
}

t_kind	get_token_kind(t_handle *h)
{
	if (h->had_sq && !h->had_dq && !h->had_plain)
		return (T_SQ);
	else if (h->had_dq && !h->had_sq && !h->had_plain)
		return (T_DQ);
	else
		return (T_PLAIN);
}

int	check_marks(t_handle *hd, char c)
{
	if (c == '\'' && !hd->in_dq)
	{
		hd->in_sq = !hd->in_sq;
		if (!hd->in_sq)
			hd->had_sq = 1;
		return (1);
	}
	if (c == '"' && !hd->in_sq)
	{
		hd->in_dq = !hd->in_dq;
		if (!hd->in_dq)
			hd->had_dq = 1;
		return (1);
	}
	return (0);
}

int	appened_char_buf(t_handle *hd, char c)
{
	hd->buf = buf_append(hd->buf, c);
	if (!hd->buf)
		return (-2);
	if (hd->in_sq)
		hd->had_sq = 1;
	if (hd->in_dq)
		hd->had_dq = 1;
	else
		hd->had_plain = 1;
	return (0);
}
