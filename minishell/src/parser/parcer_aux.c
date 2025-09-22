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

static char *gnl_simple(int fd)
{
    char buf[1024];
    int i = 0, r;
    char c;

    while ((r = read(fd, &c, 1)) > 0)
    {
        if (c == '\n')
            break;
        buf[i++] = c;
    }
    if (r <= 0 && i == 0)
        return NULL;
    buf[i] = '\0';
    return strdup(buf);
}

static void	heredoc_sigint(int sig)
{
	(void)sig;
	// write(STDOUT_FILENO, "\n", 1);
	_exit(130);
}

// static void	handler_sigint(void)
// {
// 	write(STDOUT_FILENO, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	// rl_redisplay();
// }

void	init_signals_heredoc(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = heredoc_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
// void	init_signals(void)
// {
// 	struct sigaction	sa;

// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_handler = handler_sigint;
// 	sa.sa_flags = 0;
// 	sigaction(SIGINT, &sa, NULL);
// 	sa.sa_handler = SIG_IGN;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sigaction(SIGQUIT, &sa, NULL);
// }
// void	restart_signals_shell(void)
// {
// 	struct sigaction sa;

// 	printf("entra a las señales de shell");
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_handler = handler_sigint();
// 	sa.sa_flags = 0;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }

int	read_heredoc(char *delim, t_shell *sh)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
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
			write(1, "HEREDOC> ", 9);
			line = gnl_simple(STDIN_FILENO);
			if (!line)
				exit(0);
			line[strcspn(line, "\n")] = '\0';
			if (strcmp(line, delim) == 0)
			{
				free(line);
				break ;
			}
			write(pipefd[1], line, strlen(line));
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
		waitpid(pid, &status, 0);
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130) ||
	(WIFSIGNALED(status) && WTERMSIG(status) == SIGINT))
	{
		sh->error_heredoc = 1;
		close(pipefd[0]);
		init_signals();
		return (-1);
	}
		init_signals();
	}
	return (pipefd[0]);
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
