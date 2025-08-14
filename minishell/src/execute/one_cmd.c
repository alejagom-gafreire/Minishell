/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:20:50 by alejogogi         #+#    #+#             */
/*   Updated: 2025/08/03 19:21:45 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*check_absolute_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

char	*find_executable(char *cmds, char **envp)
{
	char	*abs_path;
	char	*path_env;
	char	*full_path;
	char	*temp;
	char	**paths;
	int	i;

	i = 0;
	abs_path = check_absolute_path(cmds);
	if (abs_path)
		return (abs_path);
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmds);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	return (free_split(paths), NULL);
}

void	exec_cmd(t_parcer *list, char **envp)
{
	char	*cmd_path;
	char 	**exec_cmd;

	exec_cmd = ft_split(list->cmd_args, ' ');
	if (!exec_cmd)
		return ;
	cmd_path = find_executable(exec_cmd[0], envp);
	if (!cmd_path)
	{
		free_split(exec_cmd);
		return ;
	}
	if (execve(cmd_path, exec_cmd, envp) == -1)
	{
		free(cmd_path);
		free_split(exec_cmd);
		return ;
	}
}

void    execute_cmd(t_mini *mini, char **envp)
{
	t_parcer *list;
	pid_t	pid;
	int	status;

	list = mini->parcer;
	printf("el comando es este: %s\n", list->cmd_args);
	pid = fork();
	if (pid == 0)
	{
		exec_cmd(list, envp);
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}