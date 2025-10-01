/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-29 15:51:12 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-29 15:51:12 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_part(char **dst, const char *add)
{
	char	*tmp;

	if (!dst || !*dst)
		return (1);
	tmp = ft_strjoin(*dst, add);
	if (!tmp)
	{
		free(*dst);
		*dst = NULL;
		return (1);
	}
	free(*dst);
	*dst = tmp;
	return (0);
}

int	append_minish(char **p)
{
	if (append_part(p, BRIGHT_GREEN BOLD))
		return (1);
	if (append_part(p, "Minishell"))
		return (1);
	if (append_part(p, RESET))
		return (1);
	if (append_part(p, ": "))
		return (1);
	return (0);
}
