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

int	ft_env(t_shell *envp)
{
	int	i;

	i = 0;
	while(envp->envi[i] != NULL)
	{
		printf("%s\n",envp->envi[i]);
		i++;
	}
	return (0);
}

t_tokens	compare_buildings(char *word)
{
	t_tokens	type;

	(void)word;
	if (ft_strcmp("cd", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("echo", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("env", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("pwd", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("export", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("unset", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("exit", word) == 0)
		type = T_BUILDINGS;
	else
	    type = T_NAME_CMD;
	return (type);
}