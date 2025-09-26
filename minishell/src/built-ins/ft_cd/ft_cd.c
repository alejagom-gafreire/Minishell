/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 08:22:57 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-04 08:22:57 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_case_dash(char **target, t_shell *envp, int *mode)
{
	char	*old;

	old = get_env("OLDPWD", envp->envi);
	if (!old || !*old)
		return (printf("cd: OLDPWD not set\n"), 1);
	*target = ft_strdup(old);
	if (!*target)
		return (printf("cd: allocation error\n"), 1);
	*mode = 3;
	return (0);
}

static int	resolve_target(char **cmd, t_shell *envp, char **target, int *mode)
{
	char	*arg;

	*mode = 0;
	arg = cmd[1];
	if (!arg || (arg[0] == '~' && arg[1] == '\0'))
		return (cd_case_home_root(target, envp, mode));
	if (arg[0] == '~' && arg[1] == '/')
		return (cd_case_home_path(target, envp, arg, mode));
	if (arg[0] == '-' && arg[1] == '\0')
		return (cd_case_dash(target, envp, mode));
	*target = arg;
	return (0);
}

static int	cd_try_chdir(char *target, char *old_pwd, int mode)
{
	if (chdir(target) == -1)
	{
		printf("cd: %s: No such file or directory\n", target);
		if (old_pwd)
			free(old_pwd);
		if (mode == 1 || mode == 3)
			free(target);
		return (1);
	}
	return (0);
}

static char	*cd_update_and_pwd(char *old_pwd, char *target, t_shell *envp,
		int mode)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup(target);
	updt_pwd(old_pwd, pwd, envp);
	if (mode == 3)
		printf("%s\n", pwd);
	return (pwd);
}

int	exec_cd(char **cmd, t_shell *envp)
{
	char	*target;
	char	*old_pwd;
	char	*pwd;
	int		mode;

	if (get_size(cmd) > 2)
		return (printf("cd: too many arguments\n"), 1);
	if (resolve_target(cmd, envp, &target, &mode))
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (cd_try_chdir(target, old_pwd, mode))
		return (1);
	pwd = cd_update_and_pwd(old_pwd, target, envp, mode);
	free_cd(pwd, old_pwd, target, mode);
	return (0);
}
