/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:45 by alejogogi         #+#    #+#             */
/*   Updated: 2025/08/03 19:21:40 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	handle_redirections(t_execute *exec)
// {
// 	if (exec->infile != -1)
// 	{
// 		dup2(exec->infile, STDIN_FILENO);
// 		close(exec->infile);
// 	}
// 	if (exec->outfile == -1)
// 	{
// 		printf("Error outifle\n");
// 		exit(1);
// 	}
// 	dup2(exec->outfile, STDOUT_FILENO);
// 	close(exec->outfile);
// }

// void	execute_command(t_execute *exec, char *cmd, char **envp)
// {
// 	char	*cmd_path;
// 	char	**exec_cmd;

// 	handle_redirections(exec);
// 	exec_cmd = prepare_command(cmd);
// 	cmd_path = find_executable(exec_cmd[0], envp, exec);
// 	if (!cmd_path)
// 	{
// 		free_split(exec_cmd);
// 		printf("Error cmd_path\n");
// 		exit(1);
// 	}
// 	if (execve(cmd_path, exec_cmd, envp) == -1)
// 	{
// 		free_split(exec_cmd);
// 		printf("Error execve\n");
// 		exit(1);
// 	}
// }

// void	create_child(t_mini *mini, t_parcer *list, char **envp)
// {
// 	pid_t	pid1;

// 	pid1 = fork();
// 	if (pid1 < 0)
// 	{
// 		printf("Error PID\n");
// 		exit(1);
// 	}
// 	if (pid1 == 0)
// 	{
// 		execute_command(mini->exec, list->cmd_args, envp);
// 	}
// 	waitpid(pid1, NULL, 0);
// }

// void	create_process(t_mini *mini, char **envp)
// {
// 	t_parcer	*list;

// 	list = mini->parcer;
// 	// mini->exec->infile = open(list->name_infile, O_RDONLY);
// 	// if (mini->exec->infile == -1)
// 	// 	printf("Error open infile\n");
// 	// mini->exec->outfile = open(list->name_outfile, O_WRONLY | O_CREAT | O_TRUNC,
// 	// 		0644);
// 	// if (mini->exec->outfile == -1)
// 	// 	printf("Error open outfile\n");
// 	create_child_processes(mini, list, envp);
// 	// if (mini->exec->infile != -1)
// 	// 	close(mini->exec->infile);
// 	// if (mini->exec->outfile != -1)
// 	// 	close(mini->exec->outfile);
// }

// buscar los comandos en el path
// hacerlos si se le quita las variables de entorno
// > elimina si existe y añade lo nuevo TRUCATE
// >> si existe el archivo lo añade al final del archivo O_APPEND.
