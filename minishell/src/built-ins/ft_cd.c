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

static int	get_size(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static char	*get_home_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME", 4) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}
/*
	argv[0] = "cd"
	argv[1] = ruta (debe existir)
	env = nuestro env/ tiene que estar el pwd
*/

/*
	IMPLEMENTAR PWD Y OLDPWD

	char *ruta = argv[1];
	char *oldpwd = &ruta;
	cambiar directorio

	char *nueva = getcwd(NULL,0);
	if (nueva == NULL)
	{
		printf("cd");
		return(1);
	}

	actualizar variables de entorno
	if (oldpwd != NULL)
		set_env(entorno,"OLDPWD",oldpwd)
		set_env(entorno,"PWD",nueva)

	free(nueva);
*/

static void	updt_pwd(const char *old_pwd, const char *new_pwd, t_shell *envp)
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

int	exec_cd(char **cmd, t_shell *envp)
{
	int		nbr;
	char	*target;
	char	*old_pwd;
	char	*pwd;
	int		print_after;
	int		free_target;

	print_after = 0;
	free_target = 0;
	nbr = get_size(cmd);
	if (nbr > 2)
		return (printf("cd: too many arguments\n"), 1);

	if (!cmd[1] || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
	{
		char *home = get_home_env(envp->envi);
		if (!home || !*home)
			return (printf("cd: HOME not set\n"), 1);
		target = ft_strdup(home);
		if (!target)
			return (printf("cd: allocation error\n"), 1);
		free_target = 1;
	}
	else if (cmd[1][0] == '~' && cmd[1][1] == '/')
	{
		char *home = get_home_env(envp->envi);
		if (!home || !*home)
			return (printf("cd: HOME not set\n"), 1);
		target = ft_strjoin(home, cmd[1] + 1);
		if (!target)
			return (printf("cd: allocation error\n"), 1);
		free_target = 1;
	}
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
	{
		char *old = get_env("OLDPWD", envp->envi);
		if (!old || !*old)
			return (printf("cd: OLDPWD not set\n"), 1);
		target = ft_strdup(old);
		if (!target)
			return (printf("cd: allocation error\n"), 1);
		free_target = 1;
		print_after = 1;
	}
	else
		target = cmd[1];
	old_pwd = getcwd(NULL, 0);
	if (chdir(target) == -1)
	{
		printf("cd: %s: No such file or directory\n", target);
		if (old_pwd) free(old_pwd);
		if (free_target) free(target);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup(target);

	updt_pwd(old_pwd, pwd, envp);
	if (print_after)
		printf("%s\n", pwd);
	if (old_pwd) 
		free(old_pwd);
	if (pwd) 
		free(pwd);
	if (free_target) 
		free(target);
	return (0);
}
