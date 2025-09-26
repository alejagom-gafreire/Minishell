/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-26 20:36:42 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-26 20:36:42 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	free_cd(char *pwd, char *old_pwd, char *target, int mode)
{
	if (old_pwd)
		free(old_pwd);
	if (pwd)
		free(pwd);
	if (mode == 1 || mode == 3)
		free(target);
}

void	updt_pwd(const char *old_pwd, const char *new_pwd, t_shell *envp)
{
	char	*tmp;

	if (old_pwd)
	{
		tmp = ft_strjoin("OLDPWD=", old_pwd);
		if (tmp)
		{
			add_update_env(tmp, &envp->envi);
			free(tmp);
		}
	}
	if (new_pwd)
	{
		tmp = ft_strjoin("PWD=", new_pwd);
		if (tmp)
		{
			add_update_env(tmp, &envp->envi);
			free(tmp);
		}
	}
}

int	cd_case_home_root(char **target, t_shell *envp, int *mode)
{
	char	*home;

	home = get_env("HOME", envp->envi);
	if (!home || !*home)
		return (printf("cd: HOME not set\n"), 1);
	*target = ft_strdup(home);
	if (!*target)
		return (printf("cd: allocation error\n"), 1);
	*mode = 1;
	return (0);
}

int	cd_case_home_path(char **target, t_shell *envp, const char *arg, int *mode)
{
	char	*home;
	char	*tmp;

	home = get_env("HOME", envp->envi);
	if (!home || !*home)
		return (printf("cd: HOME not set\n"), 1);
	tmp = ft_strjoin(home, arg + 1);
	if (!tmp)
		return (printf("cd: allocation error\n"), 1);
	*target = tmp;
	*mode = 1;
	return (0);
}
