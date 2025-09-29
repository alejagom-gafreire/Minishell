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

static int	handle_single_builtin(t_mini *mini, t_parcer *list, t_shell *envp)
{
	if (mini->num_cmd == 1 && list->builtin != NULL && list->infile == -1
		&& list->outfile == -1)
	{
		envp->last_status = exec_builtins(list, list->argv, envp);
		return (1);
	}
	return (0);
}

void	init_proccess(t_mini *mini, pid_t *pids, int pipes[][2], t_shell *envp)
{
	t_parcer	*list;

	envp->error_redirect = 0;
	list = mini->parcer;
	if (!list || list->syntax_error || envp->error_redirect)
	{
		envp->last_status = 2;
		return ;
	}
	if (handle_single_builtin(mini, list, envp))
		return ;
	handle_child_process(mini, pids, pipes, envp);
}
