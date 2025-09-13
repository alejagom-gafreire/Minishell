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

int	exec_buildings(t_parcer *list,char **argv, t_shell *envp)
{
	if (ft_strcmp("env", list->building) == 0)
		return (exec_env(envp, list));
	else if (ft_strcmp("cd", list->building) == 0)
		return (exec_cd(argv,envp));
	else if (ft_strcmp("echo", list->building) == 0)
		return (exec_echo(argv));
	else if (ft_strcmp("pwd", list->building) == 0)
		return (exec_pwd());
	else if (ft_strcmp("export", list->building) == 0)
		return (ft_export(envp, list), envp->last_status);
	else if (ft_strcmp("unset", list->building) == 0)
		return (ft_unset(envp, list));
	else if (ft_strcmp("exit", list->building) == 0)
		return (exec_exit(argv));
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
