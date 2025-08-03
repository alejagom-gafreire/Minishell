/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:21:25 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/03 13:53:50 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// borrar ??
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

// crear prompt
// comprobar token
/*
	if !line => // Ctrl+D
	if *line=> // guarda en historial si no está vacío
*/
int	check_token(int argc, char *argv[], char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("parshell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		check_line(line, envp);
		free(line);
	}
	return (0);
}

// --------------------------------------------------------------------
// demo custom_promt
// char	*create_prompt(void)
// {
//     // variables prompt
// 	char		*user;
// 	const char	*emoji = "🧠 ";
// 	const char	*middle = " in ";
// 	const char	*end = " ➤ ";
// 	size_t		size;
// 	char		*prompt;

// 	user = getenv("USER");
// 	if (!user)
// 		user = "user"; // valor por defecto
// 	char *cwd = getcwd(NULL, 0); // getcwd devuelve malloc
// 	if (!cwd)
// 		cwd = strdup("unknown"); // por si falla getcwd
// 	// calcular tamaño total
// 	size = strlen(emoji) + strlen(GREEN) + strlen(user) + strlen(RESET)
// 		+ strlen(middle) + strlen(BLUE) + strlen(cwd) + strlen(RESET)
// 		+ strlen(end) + 1;
// 	prompt = malloc(size);
// 	if (!prompt)
// 	{
// 		free(cwd);
// 		return (NULL);
// 	}
// 	// construir el prompt con sprintf
// 	sprintf(prompt, "%s%s%s%s%s%s%s%s%s", emoji, GREEN, user, RESET, middle,
// 		BLUE, cwd, RESET, end);
// 	free(cwd); // liberar getcwd
// 	return (prompt);
// }