/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-27 22:16:48 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-27 22:16:48 by gafreire         ###   ########.fr       */
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

static int	setup_pipes(t_mini *mini, int (**pipes)[2])
{
	if (safe_pipes(mini, &(*pipes)))
		return (1);
	if (init_pipes(mini, (*pipes)) == -1)
	{
		free(*pipes);
		return (1);
	}
	return (0);
}

void	execute_cmd(t_mini *mini, t_shell *envp)
{
	int		(*pipes)[2];
	int		handled;
	pid_t	*pids;

	if (!mini->parcer || mini->parcer->syntax_error)
	{
		check_last_status(mini, envp);
		return ;
	}
	pipes = NULL;
	pids = malloc(sizeof(pid_t) * mini->num_cmd);
	if (!pids)
		return ;
	if (mini->num_cmd > 1 && setup_pipes(mini, &pipes))
	{
		free(pids);
		return ;
	}
	handled = init_proccess(mini, pids, pipes, envp);
	if (handled == 0)
		wait_and_cleanup(mini, pipes, pids, envp);
	free(pids);
}
