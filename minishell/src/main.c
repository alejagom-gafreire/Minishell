/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:09:27 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/08 10:52:18 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Limpia la linea
	Crea un nuevo prompt
*/
static void	handler_sigint(int sign)
{
	(void)sign;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
	Modifica las acciones de Ctrl+C y Ctrl+\
*/
int	main(int argc, char *argv[], char **envp)
{
	struct sigaction	sa;

	if (argc == 1)
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = handler_sigint;
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGQUIT, &sa, NULL);
		check_token(argc, argv, envp);
	}
	else
		printf("Error\n");
	return (0);
}
