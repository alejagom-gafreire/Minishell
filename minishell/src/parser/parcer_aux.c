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

// Ctrl+C (SIGINT): si el usuario interrumpe en medio del heredoc, debes cancelar el heredoc y limpiar.
// → Aquí se suele hacer un fork especial para el heredoc y el padre espera.

// Expandir variables $VAR dentro del heredoc (a menos que el delimitador esté entre comillas).
// → Eso lo puedes añadir después con una función de expansión.

// Liberar memoria: ojo con leaks de line.

int	read_heredoc(char *delim)
{
	int	pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("HEREDOC>"); //el prompt
		if (!line) //manejar Ctrl + c cerrar el heredoc sin cerrar la mini.
		{
			printf("Error heredoc\n");
			break;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
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
