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

static int	get_node_index(t_mini *mini, t_parcer *node)
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

static void	child_exec(t_parcer *list, t_mini *mini, int pipes[][2],
		t_shell *envp)
{
	int		i;
	char	**argv;

	i = get_node_index(mini, list);
	fd_redirect(&list, &i, mini, pipes);
	close_pipes(pipes, mini->num_cmd - 1);
	if (list->infile != -1)
		close(list->infile);
	if (list->outfile != -1)
		close(list->outfile);
	if (list->builtin)
	{
		argv = builtin_argv(list->builtin, list->cmd_args);
		if (!argv)
			exit(1);
		envp->last_status = exec_builtins(list, argv, envp);
		free_split(argv);
		exit(envp->last_status);
	}
	exec_cmd(list, envp->envi);
	perror("exec");
	exit(EXIT_FAILURE);
}

void	init_proccess(t_mini *mini, pid_t *pids, int pipes[][2], t_shell *envp)
{
	int			i;
	t_parcer	*list;
	char		**argv;

	envp->error_redirect = 0;
	list = mini->parcer;
	if (mini->num_cmd == 1 && list->builtin != NULL && list->infile == -1
		&& list->outfile == -1)
	{
		argv = builtin_argv(list->builtin, list->cmd_args);
		if (!argv)
			return ;
		envp->last_status = exec_builtins(list, argv, envp);
		free_split(argv);
		return ;
	}
	i = 0;
	while (i < mini->num_cmd)
	{
		if (list->syntax_error || list->redir_error)
		{
			envp->last_status = 1;
			if (i > 0)
				close(pipes[i - 1][0]);
			if (i < mini->num_cmd - 1)
				close(pipes[i][1]);
			pids[i] = -1;
			list = list->next;
			i++;
			continue ;
		}
		pids[i] = fork();
		if (pids[i] == 0)
			child_exec(list, mini, pipes, envp);
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
		if (pids[i] == -1)
		{
			i++;
			continue ;
		}
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		i++;
	}
	return (last_status);
}
