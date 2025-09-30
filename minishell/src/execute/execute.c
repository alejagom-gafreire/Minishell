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

/* Devuelve 1 si hay que abortar ejecución.
   Fija sh->last_status = 2 para sintaxis, = 1 para error de redirección. */
int	preflight_syntax(t_parcer *n, t_shell *sh)
{		
	/* ⚠️ No abortes por sh->error_redirect > 0 (puede venir de una línea previa) */
	if (sh->error_redirect == -1)
		return (sh->last_status = 2, 1);  /* sintaxis global severa */

	/* Sin comandos -> no abortamos: dejamos que el llamador decida (no ejecutar) */
	if (!n)
		return (0);

	while (n)
	{
		if (n->syntax_error)
			return (sh->last_status = 2, 1);  /* error de sintaxis en algún nodo */
		if (n->redir_error)
			return (sh->last_status = 1, 1);  /* error de redirección en algún nodo */
		n = n->next;
	}
	return (0);
}

// static int	preflight_syntax(t_mini *mini, t_shell *sh)
// {
// 	t_parcer	*n;

// 	n = mini->parcer;
// 	if (!n)
// 		return (sh->last_status = 2, 1);
// 	if (sh->error_redirect == -1)
// 		return (sh->last_status = 2, 1);
// 	while (n)
// 	{
// 		if (n->syntax_error)
// 			return (sh->last_status = 2, 1);
// 		if (n->redir_error)
// 			return (sh->last_status = 1, 1);
// 		n = n->next;
// 	}
// 	if (sh->error_redirect)
// 		return (sh->last_status = 1, 1);
// 	return (0);
// }


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
	int			(*pipes)[2];
	int			handled;
	pid_t		*pids;
	t_parcer	*cmd;

	/* (A) preflight SOLO con la lista actual */
	if (preflight_syntax(mini->parcer, envp))
		return;

	cmd = mini->parcer;

	/* (B) Elimina este check antiguo que podía cortar válidos:
	if (!cmd || cmd->syntax_error) { check_last_status(mini, envp); return; }
	   -> Si !cmd, simplemente no hacemos nada; si hay sintaxis, ya salimos arriba.
	*/

	/* ejecutar builtin en el padre SIN malloc (sin redirs) */
	if (mini->num_cmd == 1 && cmd && cmd->builtin != NULL
		&& cmd->infile == -1 && cmd->outfile == -1)
	{
		envp->last_status = exec_builtins(cmd, cmd->argv, envp);
		return;
	}

	/* malloc pids SOLO si vamos a forkar */
	pipes = NULL;
	pids = malloc(sizeof(pid_t) * (mini->num_cmd > 0 ? mini->num_cmd : 1));
	if (!pids)
	{
		envp->last_status = 1;
		return;
	}

	/* solo si hay pipes */
	if (mini->num_cmd > 1 && setup_pipes(mini, &pipes))
	{
		free(pids);
		envp->last_status = 1; /* (C) deja status coherente si falla pipes */
		return;
	}

	handled = init_proccess(mini, pids, pipes, envp);
	if (handled == 0)
		wait_and_cleanup(mini, pipes, pids, envp);

	free(pids);
}

// void	execute_cmd(t_mini *mini, t_shell *envp)
// {
// 	int		(*pipes)[2];
// 	int		handled;
// 	pid_t	*pids;

// 	if (!mini->parcer || mini->parcer->syntax_error)
// 	{
// 		check_last_status(mini, envp);
// 		return ;
// 	}
// 	pipes = NULL;
// 	pids = malloc(sizeof(pid_t) * mini->num_cmd);
// 	if (!pids)
// 		return ;
// 	if (mini->num_cmd > 1 && setup_pipes(mini, &pipes))
// 	{
// 		free(pids);
// 		pids = NULL;
// 		return ;
// 	}
// 	handled = init_proccess(mini, pids, pipes, envp);
// 	if (handled == 0)
// 		wait_and_cleanup(mini, pipes, pids, envp);
// 	free(pids);
// 	pids = NULL;
// }
