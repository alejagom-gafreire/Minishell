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

// #include "minishell.h"

// // void	first_child(int *pipe, pid_t *pid, char **envp, t_parcer *list)
// // {
// // 	int	fd;
// // 	if (list->name_infile)
// // 	{
// // 		fd = open(list->name_infile, O_RDONLY);
// // 	}
// // 	*pid = fork();
// // 	if (*pid == 0)
// // 	{
// // 		close(pipe[READ_END]); //cierro el extremo que no voy a usar.
// // 		dup2(pipe[WRITE_END], STDOUT_FILENO); //escribo en el pipe.
// // 		close(pipe[WRITE_END]); //cierro el pipe despues de usarlo.
// // 	}
// // }

// // static char	**prepare_command(char *cmd)
// // {
// // 	char	**exec_cmd;

// // 	exec_cmd = ft_split(cmd, ' ');
// // 	if (!exec_cmd)
// // 	{
// // 		printf("Error exec_cmd\n");
// // 		exit(1);
// // 	}
// // 	return (exec_cmd);
// // }

// void	handle_redirections(t_parcer *list)
// {
// 	int	fd;

// 	if (list->name_infile)
// 	{
// 		fd = open(list->name_infile, O_RDONLY);
// 		if (fd < 0)
// 			exit(1);
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	if (list->name_outfile)
// 	{
// 		fd = open(list->name_outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd < 0)
// 			exit(1);
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// }

// // void	execute_command(t_parcer *list, char **envp)
// // {
// // 	char	*cmd_path;
// // 	char	**exec_cmd;

// // 	printf("tiene esto \n");
// // 	handle_redirections(list);
// // 	exec_cmd = ft_split(list->cmd_args, ' ');
// // 	cmd_path = find_executable(exec_cmd[0], envp, list->exec);
// // 	if (!cmd_path)
// // 	{
// // 		printf("Error cmd_path\n");
// // 		exit(1);
// // 	}
// // 	if (execve(cmd_path, exec_cmd, envp) == -1)
// // 	{
// // 		printf("Error execve\n");
// // 		exit(1);
// // 	}
// // }

// void	child_process(int i, int cmds, int pipes[cmds - 1][2], t_parcer *list, char **envp)
// {
// 	int	j;

// 	j = 0;
// 	if (i > 0)
// 		dup2(pipes[i - 1][READ_END], STDIN_FILENO); //leemos del pipe anterior
// 	if (i < cmds - 1)
// 		dup2(pipes[i][WRITE_END], STDOUT_FILENO); //escribimos en el pipe siguiente
// 	while (j < cmds - 1)
// 	{
// 		close(pipes[j][READ_END]);
// 		close(pipes[j][WRITE_END]);
// 		j++;
// 	}
// 	//handle_redirections(list);
// 	execute_command(list, envp);
// }

// void	init_forks(int (*pipes)[2], pid_t *pids, char **envp, t_mini *mini)
// {
// 	int	i;
// 	int	cmds;
// 	t_parcer *list;

// 	cmds = mini->exec->cmds;
// 	list = mini->parcer;
// 	i = 0;
// 	while (i < cmds)
// 	{
// 		printf("OUTFILEtiene esto: \n");
// 		pids[i] = fork();
// 		if (pids[i] == 0)
// 			child_process(i, cmds, pipes, list, envp);
// 		list = list->next;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < cmds)
// 	{
// 		close(pipes[i][READ_END]);
// 		close(pipes[i][WRITE_END]);
// 		i++;
// 	}
// 	i = 0;
// 	while(i < cmds)
// 	{
// 		waitpid(pids[i], NULL, 0);
// 		i++;
// 	}
// }

// int	init_pipes(int	cmds, int pipes[cmds - 1][2])
// {
// 	int	i;

// 	i = 0;
// 	while (i < cmds - 1)
// 	{
// 		if (pipe(pipes[i]) == -1)
// 		{
// 			return (-1);
// 		}
// 	}
// 	return (0);
// }

// // char *find_executable(char *cmd, char **envp)
// // {
// //     // Si el comando ya contiene '/', asumimos que es ruta absoluta o relativa
// //     if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
// //         return cmd;

// //     // Buscar en PATH
// //     char *path_env = NULL;
// //     for (int i = 0; envp[i]; i++) {
// //         if (strncmp(envp[i], "PATH=", 5) == 0) {
// //             path_env = envp[i] + 5;
// //             break;
// //         }
// //     }
// //     if (!path_env)
// //         return NULL;

// //     char *path_dup = strdup(path_env);
// //     char *token = strtok(path_dup, ":");
// //     while (token) {
// //         char full_path[1024];
// //         snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
// //         if (access(full_path, X_OK) == 0) {
// //             free(path_dup);
// //             return strdup(full_path);
// //         }
// //         token = strtok(NULL, ":");
// //     }
// //     free(path_dup);
// //     return NULL;
// // }

// void execute_command(t_parcer *list, char **envp)
// {
//     pid_t pid;
//     int status;
//     char **argv;
//     char *cmd_path;

//     argv = ft_split(list->cmd_args, ' ');
//     if (!argv)
//     {
//         fprintf(stderr, "Error al hacer split del comando\n");
//         exit(1);
//     }
//     cmd_path = find_executable(argv[0], envp);
//     if (!cmd_path)
//     {
//         fprintf(stderr, "%s: command not found\n", argv[0]);
//         exit(127);
//     }
//     pid = fork();
//     if (pid == 0)
//     {
//         execve(cmd_path, argv, envp);
//         perror("execve");
//         exit(126);
//     }
//     else if (pid > 0)
//     {
//         waitpid(pid, &status, 0);
//     }
//     else
//     {
//         perror("fork");
//         exit(1);
//     }
// }

// // void	init_one_cmd(t_parcer *list, char **envp)
// // {
// // 	char **cmd;
// // 	int	status;
// // 	pid_t	pid;

// // 	cmd = ft_split(list->cmd_args, ' ');
// // 	pid = fork();
// // 	if (pid == 0)
// // 	{

// // 	}
// // }

// void    start_execute(t_mini *mini, char **envp)
// {
// 	int	cmds = mini->exec->cmds;
// 	int	pipes[cmds - 1][2];
// 	pid_t	pids[mini->exec->cmds];
// 	t_parcer *list;

// 	list = mini->parcer;
// 	if (list && cmds == 1 && list->next == NULL)
// 		execute_command(list, envp);
// 	if (init_pipes(mini->exec->cmds, pipes) == -1)
// 		return ;
// 	init_forks(pipes, pids, envp, mini);
// }

//  < infile.txt ls -l > out.txt
