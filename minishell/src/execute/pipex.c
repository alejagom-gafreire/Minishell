/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:45 by alejogogi         #+#    #+#             */
/*   Updated: 2025/08/03 14:08:35 by alejogogi        ###   ########.fr       */
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

char	*find_executable(char *cmd, char **envp, t_execute *exec)
{
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	exec->abs_path = check_absolute_path(cmd);
	if (exec->abs_path)
		return (exec->abs_path);
	exec->path_env = get_path_env(envp);
	if (!exec->path_env)
		return (NULL);
	paths = ft_split(exec->path_env, ':');	
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		exec->full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(exec->full_path, X_OK) == 0)
			return (free_split(paths), exec->full_path);
		free(exec->full_path);
		i++;
	}
	return (free_split(paths), NULL);
}

void    execute_command(t_execute *exec, char *cmd, char **envp)
{
    char    *cmd_path;
    char    **exec_cmd;

    if (exec->infile != -1)
    {
        dup2(exec->infile, STDIN_FILENO);
        close(exec->infile);
    }
    if (exec->outfile == -1)
    {
	    printf("Error outifle\n");
	    exit(1);
    }
    dup2(exec->outfile, STDOUT_FILENO);
    close(exec->outfile);
    
    exec_cmd = ft_split(cmd, ' ');
    if (!exec_cmd)
    {
	    printf("Error exec_cmd\n");
	    exit(1);
    }    
    cmd_path = find_executable(exec_cmd[0], envp, exec);
    if (!cmd_path)
    {
	    free_split(exec_cmd);
	    printf("Error cmd_path\n");
	    exit(1);
    }    
    if (execve(cmd_path, exec_cmd, envp) == -1)
    {
	free_split(exec_cmd);
	printf("Error execve\n");
	exit(1);
    }
}

void	create_child(t_mini *mini, t_parcer *list, char **envp)
{
	pid_t 	pid1;

	pid1 = fork();
	if (pid1 < 0)
	{
		printf("Error PID\n");
		exit(1);
	}
	if (pid1 == 0)
	{
		execute_command(mini->exec, list->cmd_args, envp);
	}
	waitpid(pid1, NULL, 0);
}

void	create_process(t_mini *mini, char **envp)
{
	t_parcer	*list;

	list = mini->parcer;
	mini->exec->infile = open(list->name_infile, O_RDONLY);
	if (mini->exec->infile == -1)
		printf("Error open infile\n");
	mini->exec->outfile = open(list->name_outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mini->exec->outfile == -1)
		printf("Error open outfile\n");
	create_child(mini, list, envp);
	if (mini->exec->infile != -1)
		close(mini->exec->infile);
	if (mini->exec->outfile != -1)
		close(mini->exec->outfile);
}

//contar la cantidad de comandos que hay separados por pipes
//crear un pipe por cada par de comandos
//crear los procesos hijos (fork)
//buscar los comandos en el path
//hacerlos si se le quita las variables de entorno
// > elimina si existe y añade lo nuevo TRUCATE
// >> si existe el archivo lo añade al final del archivo O_APPEND.
