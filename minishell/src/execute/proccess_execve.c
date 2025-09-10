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

void	fd_redirect(t_parcer **list, int *i, t_mini *mini, int pipes[][2])
{
	if ((*list)->infile != -1)
		dup2((*list)->infile, STDIN_FILENO);
	else if (*i > 0)
		dup2(pipes[*i - 1][0], STDIN_FILENO);
	if ((*list)->outfile != -1)
		dup2((*list)->outfile, STDOUT_FILENO);
	else if (*i < mini->num_cmd - 1)
		dup2(pipes[*i][1], STDOUT_FILENO);
}

void	exec_cmd(t_parcer *list, char **envp)
{
	char	*cmd_path;
	char	**exec_cmd;

	exec_cmd = ft_split(list->cmd_args, ' ');
	if (!exec_cmd)
		return ;
	cmd_path = find_executable(exec_cmd[0], envp);
	if (!cmd_path)
	{
		free_split(exec_cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, exec_cmd, envp) == -1 && list->cmd_args)
	{
		free(cmd_path);
		free_split(exec_cmd);
		return ;
	}
}

static char	**builtin_argv(const char *name, const char *args_str)
{
	char	**argv;
	char	**args;
	int		i;
	int		z;

	if (!name)
		return (NULL);
	if (!args_str || args_str[0] == '\0')
	{
		argv = malloc(sizeof(char *) * 2);
		if (!argv)
			return (NULL);
		argv[0] = ft_strdup(name);
		argv[1] = NULL;
		return (argv);
	}
	args = ft_split(args_str, ' ');
	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
		i++;
	argv = malloc(sizeof(char *) * (i + 2));
	if (!argv)
		return (free_split(args), NULL);
	argv[0] = ft_strdup(name);
	z = 0;
	while (z < i)
	{
		argv[z + 1] = args[z];
		z++;
	}
	argv[i + 1] = NULL;
	return (free(args), argv);
}

void	init_proccess(t_mini *mini, pid_t *pids, int pipes[][2], t_shell *envp)
{
	int			i;
	t_parcer	*list;
	char		**argv;

	list = mini->parcer;
	i = 0;
	if (mini->num_cmd == 1 && list->building != NULL && list->infile == -1
		&& list->outfile == -1)
	{
		argv = builtin_argv(list->building, list->cmd_args);
		if (!argv)
			return ;
		envp->last_status = exec_buildings(list, argv, envp);
		free_split(argv);
		return ;
	}
	while (i < mini->num_cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			fd_redirect(&list, &i, mini, pipes);
			close_pipes(pipes, mini->num_cmd - 1);
			if (list->infile != -1)
				close(list->infile);
			if (list->outfile != -1)
				close(list->outfile);
			if (list->building != NULL)
			{
				argv = builtin_argv(list->building, list->cmd_args);
				if (!argv)
					exit(1);
				envp->last_status = exec_buildings(list, argv, envp);
				exit(envp->last_status);
			}
			else
			{
				exec_cmd(list, envp->envi);
				perror("exec");
				exit(EXIT_FAILURE);
			}
		}
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
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		i++;
	}
	return (last_status);
}
