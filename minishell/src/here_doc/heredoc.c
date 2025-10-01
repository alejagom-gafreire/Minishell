/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:41:00 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/25 17:41:03 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_line(int fd_write, char *delim)
{
	char	*line;
	char	*nl;

	while (1)
	{
		write(1, "HEREDOC>", 9);
		line = gnl_simple(STDIN_FILENO);
		if (!line)
			exit (0);
		nl = ft_strchr(line, '\n');
		if (nl)
			*nl = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
}

static void	heredoc_child(int *pipefd, char *delim)
{
	init_signals_heredoc();
	close(pipefd[0]);
	ft_line(pipefd[1], delim);
	close(pipefd[1]);
	exit(0);
}

static int	heredoc_parent(int *pipefd, pid_t pid, t_shell **shell)
{
	int	status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	waitpid(pid, &status, 0);
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130)
		|| (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT))
	{
		(*shell)->error_heredoc = 1;
		close(pipefd[0]);
		init_signals();
		return (-1);
	}
	init_signals();
	return (pipefd[0]);
}

int	read_heredoc(char *delim, t_shell *sh)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		heredoc_child(pipefd, delim);
	return (heredoc_parent(pipefd, pid, &sh));
}
