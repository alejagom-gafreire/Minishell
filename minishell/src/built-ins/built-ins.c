/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:43:45 by alejandro         #+#    #+#             */
/*   Updated: 2025/08/29 16:44:11 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	compare_buildings(char *word)
{
	t_tokens	type;

	(void)word;
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