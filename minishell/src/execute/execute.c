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

int	preflight_syntax(t_parcer *n, t_shell *sh)
{
	if (sh->error_redirect == -1)
		return (sh->last_status = 2, 1);
	if (!n)
		return (0);
	while (n)
	{
		if (n->syntax_error)
			return (sh->last_status = 2, 1);
		if (n->redir_error)
			return (sh->last_status = 1, 1);
		n = n->next;
	}
	return (0);
}

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

static int	setup_pipes(t_mini *mini, int (**pipes)[2])
{
	*pipes = malloc(sizeof(int [mini->num_cmd - 1][2]));
	if (!*pipes)
		return (1);
	if (init_pipes(mini, *pipes) == -1)
	{
		free(*pipes);
		*pipes = NULL;
		return (1);
	}
	return (0);
}

void	execute_cmd(t_mini *mini, t_shell *envp)
{
	pid_t		*pids;
	int			(*pipes)[2];
	size_t		n;

	pipes = NULL;
	if (preflight_syntax(mini->parcer, envp))
		return ;
	if (mini->num_cmd == 1 && mini->parcer && mini->parcer->builtin != NULL
		&& mini->parcer->infile == -1 && mini->parcer->outfile == -1)
		return ((void)(envp->last_status = exec_builtins(
				mini->parcer, mini->parcer->argv, envp)));
	n = (size_t)mini->num_cmd + (mini->num_cmd == 0);
	pids = malloc(sizeof(pid_t) * n);
	if (!pids)
		return ((void)(envp->last_status = 1));
	if (mini->num_cmd > 1 && setup_pipes(mini, &pipes))
		return (free(pids), (void)(envp->last_status = 1));
	if (init_proccess(mini, pids, pipes, envp) == 0)
		wait_and_cleanup(mini, pipes, pids, envp);
	free(pids);
}
