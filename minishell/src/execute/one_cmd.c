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

int	init_pipes(t_mini *mini, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < mini->num_cmd)
	{
		if (pipe(pipes[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	close_pipes(int pipes[][2], int	num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	init_proccess(t_mini *mini, pid_t *pids, int pipes[][2], char **envp)
{
	int	i;
	t_parcer 	*list;
 
	list = mini->parcer;
	i = 0;
	while (i < mini->num_cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (list->infile != -1)
				dup2(list->infile, STDIN_FILENO);
			else if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (list->outfile != -1)
				dup2(list->outfile, STDOUT_FILENO);
			else if (i < mini->num_cmd - 1)
				dup2(pipes[i][1], STDOUT_FILENO);
			close_pipes(pipes, mini->num_cmd - 1);
			if (list->infile != -1)
				close(list->infile);
			if (list->outfile != -1)
				close(list->outfile);
			exec_cmd(list, envp);
			perror("exec");
		}
		list = list->next;
		i++;
	}
}

int	wait_childrens(pid_t *pids, int num_cmd)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < num_cmd)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WIFEXITED(status); //codigo de salida.
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status); //termino por señal.
		i++;
	}
	return (last_status);
}

void    execute_cmd(t_mini *mini, char **envp)
{
	int	(*pipes)[2];
	pid_t	pids[mini->num_cmd];

	pipes = NULL;
	if(mini->num_cmd > 1)
	{
		pipes = malloc(sizeof(int[mini->num_cmd - 1][2]));
		if (!pipes)
			return ;
		if (init_pipes(mini, pipes) == -1)
		{
			free(pipes);
			return ;
		}
	}
	init_proccess(mini, pids, pipes, envp);
	if (mini->num_cmd > 1)
	{
		close_pipes(pipes, mini->num_cmd - 1);
		free(pipes);
	}
	mini->last_status = wait_childrens(pids, mini->num_cmd);
	printf("Last exit status: %d\n", mini->last_status);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	exec_cmd(list, envp);
	// 	exit(1);
	// }
	// else if (pid > 0)
	// 	waitpid(pid, &status, 0);
	// else
	// 	perror("fork");
}