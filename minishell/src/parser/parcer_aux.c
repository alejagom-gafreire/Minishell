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
static void	heredoc_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	_exit(130);
}

void	init_signals_heredoc(void)
{
	struct	sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = heredoc_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	handler_sigint_shell(int sig)
{
	(void)sig;

	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	restart_signals_shell(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler_sigint_shell;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

int	read_heredoc(char *delim, t_shell **env)
{
	int		pipefd[2];
	pid_t	pid;
	int	status;
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		init_signals_heredoc();
		close(pipefd[0]);
		while (1)
		{
			rl_catch_signals = 0;
			line = readline("HEREDOC>");
			if (!line)
				exit(0);
			if (ft_strcmp(line, delim) == 0)
			{
				free(line);
				break ;
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		exit(0);
	}
	else
	{
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		(*env)->error_heredoc = 1;   // usa 1 para marcar error
		close(pipefd[0]);
		restart_signals_shell();
		printf("DEBUG heredoc cancelado con Ctrl+C\n");
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		(*env)->error_heredoc = 1;
		close(pipefd[0]);
		restart_signals_shell();
		printf("DEBUG heredoc _exit(130)\n");
		return (-1);
	}

	restart_signals_shell();
	}
	return (pipefd[0]);
}

int	open_outfile(char *file, int appened)
{
	int	fd;

	fd = -1;
	if (appened)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("opoen");
			return (-1);
		}
	}
	else
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("opoen");
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
