/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:00:23 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/30 17:26:35 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Ctrl+C (SIGINT): si el usuario interrumpe en medio del heredoc,
		debes cancelar el heredoc y limpiar.
	→ Aquí se suele hacer un fork especial para el heredoc y el padre espera.

	Expandir variables $VAR dentro del heredoc 
	(a menos que el delimitador esté entre comillas).
	→ Eso lo puedes añadir después con una función de expansión.

	Liberar memoria: ojo con leaks de line.
*/

// static int is_cmd_word(t_tokens t)
// {
// 	 return (t == T_NAME_CMD || t == T_GENERAL || t == T_BUILTINS);
// }
/*
	manejar Ctrl + c cerrar el heredoc sin cerrar la mini.
*/

/* handler solo para heredoc */

/* heredoc.c */

static char	*gnl_simple(int fd)
{
	char		buf[1024];
	char		c;
	int			i;
	int			r;

	i = 0;
	r = read(fd, &c, 1);
	while (r > 0)
	{
		if (c == '\n')
			break ;
		if (i < 1023)
			buf[i++] = c;
		r = read(fd, &c, 1);
	}
	if (r <= 0 && i == 0)
		return (NULL);
	buf[i] = '\0';
	return (strdup(buf));
}

static void	heredoc_sigint(int sig)
{
	(void)sig;
	// write(STDOUT_FILENO, "\n", 1);
	_exit(130);
}

void	init_signals_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = heredoc_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	ft_line(int fd_write, char *delim)
{
	char	*line;

	while (1)
	{
		write(1, "HEREDOC>", 9);
		line = gnl_simple(STDIN_FILENO);
		if (!line)
			exit (0);
		line[strcspn(line, "\n")] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(fd_write, line, strlen(line));
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

int	open_outfile(char *file, int appened, t_shell **env)
{
	int	fd;

	fd = -1;
	if (appened)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
		{
			(*env)->denied_open = 1;
			return (-1);
		}
	}
	else
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			(*env)->denied_open = 1;
			return (-1);
		}
	}
	return (fd);
}

void	inside_parcer(t_parcer **head, t_parcer *new_node)
{
	t_parcer	*tmp;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}
