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

int	init_pipes(t_mini *mini, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < mini->num_cmd - 1)
	{
		if (pipe(pipes[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	close_pipes(int pipes[][2], int num_pipes)
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

int	safe_pipes(t_mini *mini, int (**pipes)[2])
{
	*pipes = malloc(sizeof (int [mini->num_cmd - 1][2]));
	if (!*pipes)
		return (1);
	return (0);
}

void	execute_cmd(t_mini *mini, char **envp)
{
	int		(*pipes)[2];
	pid_t	*pids;

	pipes = NULL;
	pids = malloc(sizeof(pid_t) * mini->num_cmd);
	if (!pids)
		return ;
	if (mini->num_cmd > 1)
	{
		if (safe_pipes(mini, &pipes))
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
	free(pids);
}
