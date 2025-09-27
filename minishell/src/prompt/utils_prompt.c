/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:59:11 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/27 17:59:13 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envi(t_shell *envi)
{
	envi->last_status = 0;
	envi->error_heredoc = 0;
	envi->error_redirect = 0;
	envi->denied_open = 0;
}

int	handle_eof(char *line, char *promt, char **envi)
{
	if (!line)
	{
		printf("exit\n");
		free(promt);
		free_split(envi);
		return (1);
	}
	return (0);
}

int	handle_empty_line(char *line, char *prompt)
{
	if (line && *line == '\0')
	{
		free(line);
		free(prompt);
		return (1);
	}
	return (0);
}
