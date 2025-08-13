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

void	exec_cmd(t_parcer *list, char **envp)
{
	char	*cmd_path;
	char	**exec_cmd;

	exec_cmd = ft_split(list->cmd_args, ' ');
	for (int i = 0; exec_cmd[i]; i++)  
    		printf("argv[%d] = %s\n", i, exec_cmd[i]);
	if (!exec_cmd)
		return ;
	cmd_path = find_executable(exec_cmd[0], envp, list->exec);
	printf("PRINTEAR ESTO %s\n", cmd_path);
	if (!cmd_path)
		return ;
	if (execve(cmd_path, exec_cmd, envp) == -1)
		return ;
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