/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-29 10:58:31 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-29 10:58:31 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_last_status(t_mini *mini, t_shell *envp)
{
	if (!mini->parcer)
	{
		envp->last_status = 2;
		return ;
	}
	if (mini->parcer->syntax_error == 127 || envp->last_status == 127)
	{
		envp->last_status = 127;
		return ;
	}
	else if (mini->parcer->syntax_error)
		envp->last_status = 2;
}

static void	child_exec(t_parcer *list, t_mini *mini, int pipes[][2],
		t_shell *envp)
{
	int	i;

	i = get_node_index(mini, list);
	fd_redirect(&list, &i, mini, pipes);
	close_pipes(pipes, mini->num_cmd - 1);
	if (list->infile != -1)
		close(list->infile);
	if (list->outfile != -1)
		close(list->outfile);
	if (list->argv && list->argv[0] && compare_builtins(list->argv[0]))
	{
		if (!list->argv || !list->argv[0])
			exit(0);
		envp->last_status = exec_builtins(list, list->argv, envp);
		exit(envp->last_status);
	}
	exec_cmd(list, envp->envi);
	perror("exec");
	exit(EXIT_FAILURE);
}

static void	pipe_close_on_err(t_child_prcs *child_prcs, int k)
{
	int	has;
	int	last;

	has = (child_prcs->mini->num_cmd > 1 && child_prcs->fds != NULL);
	last = child_prcs->mini->num_cmd - 1;
	if (has && k > 0)
		close(child_prcs->fds[k - 1][0]);
	if (has && k < last)
		close(child_prcs->fds[k][1]);
}

static void	spawn_or_exec(t_child_prcs *child_prcs, t_parcer *node, int k)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		child_prcs->pids[k] = -1;
		child_prcs->sh->last_status = 1;
		pipe_close_on_err(child_prcs, k);
		return ; // 👉 seguimos, el padre limpiará luego
	}
	if (pid == 0)
	{
		// 👶 hijo
		child_exec(node, child_prcs->mini, child_prcs->fds, child_prcs->sh);
	}
	// 👨 padre
	child_prcs->pids[k] = pid;
}
// static void	spawn_or_exec(t_child_prcs *child_prcs, t_parcer *node, int k)
// {
// 	child_prcs->pids[k] = fork();
// 	if (child_prcs->pids[k] == 0)
// 		child_exec(node, child_prcs->mini, child_prcs->fds, child_prcs->sh);
// }

void	handle_child_process(t_mini *mini, pid_t *pids, int fds[][2],
		t_shell *sh)
{
	int				k;
	t_parcer		*node;
	t_child_prcs	child_prcs;

	if (preflight_syntax(mini->parcer, sh))
	return ;
	k = 0;
	node = mini->parcer;
	child_prcs.mini = mini;
	child_prcs.sh = sh;
	child_prcs.fds = fds;
	child_prcs.pids = pids;
	while (k < mini->num_cmd && node)
	{
		// if (node->syntax_error || node->redir_error)
		// {
		// 	sh->last_status = 1;
		// 	pipe_close_on_err(&child_prcs, k);
		// 	pids[k++] = -1;
		// 	node = node->next;
		// 	continue ;
		// }
		spawn_or_exec(&child_prcs, node, k);
		k++;
		node = node->next;
	}
}
