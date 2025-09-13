/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:21:25 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/08 10:51:19 by gafreire         ###   ########.fr       */
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

static	void free_env(char **envi)
{
	int	i;
	int	ln;

	i = 0;;
	ln = 0;
	while (envi[i] != NULL)
		i++;
	while (ln < i)
	{
		free(envi[ln]);
		ln++;
	}
	free(envi);
}

static void free_enviroment(int i, char **envi)
{
	int	ln;

	ln = 0;
	while (ln < i)
	{
		free(envi[ln]);
		ln++;
	}
	free(envi);
	return ;
}

char **check_enviroment(char **envp)
{
	char	**envi_cpy;
	int	count;
	int	i;

	i = 0;
	count = 0;
	while(envp[count] != NULL)
		count++;
	envi_cpy = malloc((count + 1) * sizeof(char *));
	if (!envi_cpy) return (NULL);
	while (i < count)
	{
		envi_cpy[i] = ft_strdup(envp[i]);
		if (!envi_cpy[i])
			free_enviroment(i, envi_cpy);
		i++;
	}
	envi_cpy[count] = NULL;
	return (envi_cpy);
}

int	check_token(int argc, char *argv[], char **envp)
{
	char	*line;
	t_shell	envi;
	int	i;

	i = 0;
	envi.envi = check_enviroment(envp);
	envi.last_status = 0;
	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("parshell$ ");
		if (line && *line == '\0')
		{
			free(line);
			continue ;
		}
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		check_line(line, &envi, &i);
		free(line);
	}
	free_env(envi.envi);
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