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
		return (ft_export(envp, list));
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

static int	count_args(char **args)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (args[i++])
		count++;
	return (count);
}

static char	**copy_args(char **args, int count)
{
	char	**cpy;
	int		i;
	int		j;

	i = 1;
	j = 0;
	cpy = malloc(sizeof(char *) * (count + 1));
	if (!cpy)
		return (NULL);
	while (args[i])
	{
		cpy[j] = ft_strdup(args[i]);
		if (!cpy[j])
			return (NULL);
		i++;
		j++;
	}
	cpy[j] = NULL;
	return (cpy);
}

char	**all_args(char **args)
{
	int		count;

	count = count_args(args);
	return (copy_args(args, count));
}
