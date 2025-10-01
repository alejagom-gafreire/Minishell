/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procces_execve_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-13 13:32:38 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-13 13:32:38 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_childrens(pid_t *pids, int num_cmd)
{
	int		status;
	int		i;
	pid_t	ret;

	status = 0;
	i = 0;
	while (i < num_cmd)
	{
		if (pids[i] != -1)
		{
			ret = -1;
			while (ret == -1)
				ret = waitpid(pids[i], &status, 0);
		}
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

void	fd_redirect(t_parcer **list, int *i, t_mini *mini, int pipes[][2])
{
	if ((*list)->redir_error || (*list)->syntax_error)
	{
		if (*i > 0)
			close(pipes[*i - 1][0]);
		if (*i < mini->num_cmd - 1)
			close(pipes[*i][1]);
		exit(1);
	}
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

	if (!list->argv || !list->argv[0])
		exit(0);
	cmd_path = find_executable(list->argv[0], envp);
	if (!cmd_path)
	{
		printf("%s: command not found\n", list->argv[0]);
		exit(127);
	}
	if (execve(cmd_path, list->argv, envp) == -1)
	{
		perror(list->argv[0]);
		free(cmd_path);
		exit(126);
	}
}

static char	**build_argv(const char *name, char **args, int count)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (count + 2));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(name);
	i = 0;
	while (i < count)
	{
		argv[i + 1] = args[i];
		i++;
	}
	argv[count + 1] = NULL;
	return (argv);
}

char	**builtin_argv(const char *name, const char *args_str)
{
	char	**argv;
	char	**args;
	int		i;

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
	argv = build_argv(name, args, i);
	if (!argv)
		return (free_split(args), NULL);
	return (free(args), argv);
}
