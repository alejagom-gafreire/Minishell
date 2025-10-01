/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:11:59 by alejagom          #+#    #+#             */
/*   Updated: 2025/08/19 20:12:01 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_node_index(t_mini *mini, t_parcer *node)
{
	int			id;
	t_parcer	*tmp;

	id = 0;
	tmp = mini->parcer;
	while (tmp && tmp != node)
	{
		id++;
		tmp = tmp->next;
	}
	return (id);
}

static int	runner_builtin(t_mini *mini, t_parcer *cmd, t_shell *envp)
{
	if (!cmd || !cmd->builtin)
		return (0);
	if (mini->num_cmd == 1 && cmd->builtin != NULL && cmd->infile == -1
		&& cmd->outfile == -1)
	{
		envp->last_status = exec_builtins(cmd, cmd->argv, envp);
		return (1);
	}
	return (0);
}

int	init_proccess(t_mini *mini, pid_t *pids, int pipes[][2], t_shell *envp)
{
	t_parcer	*list;

	envp->error_redirect = 0;
	list = mini->parcer;
	if (!list || list->syntax_error || envp->error_redirect)
	{
		envp->last_status = 2;
		return (1);
	}
	if (runner_builtin(mini, list, envp))
		return (1);
	handle_child_process(mini, pids, pipes, envp);
	return (0);
}

void	wait_and_cleanup(t_mini *mini, int (*pipes)[2], pid_t *pids,
		t_shell *envp)
{
	if (mini->num_cmd > 1)
	{
		close_pipes(pipes, mini->num_cmd - 1);
		free(pipes);
	}
	envp->last_status = wait_childrens(pids, mini->num_cmd);
}
