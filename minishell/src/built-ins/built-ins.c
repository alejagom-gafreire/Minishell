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

int	exec_builtins(t_parcer *list, char **argv, t_shell *envp)
{
	if (ft_strcmp("env", list->builtin) == 0)
		return (exec_env(envp, list));
	else if (ft_strcmp("cd", list->builtin) == 0)
		return (exec_cd(argv, envp));
	else if (ft_strcmp("echo", list->builtin) == 0)
		return (exec_echo(argv));
	else if (ft_strcmp("pwd", list->builtin) == 0)
		return (exec_pwd());
	else if (ft_strcmp("export", list->builtin) == 0)
		return (ft_export(envp, list), envp->last_status);
	else if (ft_strcmp("unset", list->builtin) == 0)
		return (ft_unset(envp, list));
	else if (ft_strcmp("exit", list->builtin) == 0)
		return (exec_exit(argv));
	return (0);
}

t_tokens	compare_builtins(char *word)
{
	t_tokens	type;

	if (ft_strcmp("cd", word) == 0)
		type = T_BUILTINS;
	else if (ft_strcmp("echo", word) == 0)
		type = T_BUILTINS;
	else if (ft_strcmp("env", word) == 0)
		type = T_BUILTINS;
	else if (ft_strcmp("pwd", word) == 0)
		type = T_BUILTINS;
	else if (ft_strcmp("export", word) == 0)
		type = T_BUILTINS;
	else if (ft_strcmp("unset", word) == 0)
		type = T_BUILTINS;
	else if (ft_strcmp("exit", word) == 0)
		type = T_BUILTINS;
	else
		type = T_NAME_CMD;
	return (type);
}
