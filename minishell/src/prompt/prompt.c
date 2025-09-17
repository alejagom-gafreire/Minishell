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

static void	free_env(char **envi)
{
	int	i;
	int	ln;

	i = 0;
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

static void	free_enviroment(int i, char **envi)
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

char	**check_enviroment(char **envp)
{
	char	**envi_cpy;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (envp[count] != NULL)
		count++;
	envi_cpy = malloc((count + 1) * sizeof(char *));
	if (!envi_cpy)
		return (NULL);
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

int	check_token(char **envp)
{
	char	*line;
	char	*prompt;
	int		option;
	t_shell	envi;

	print_banner();
	spinner_loading();
	option = show_menu();
	if (option == 2 || option == 3)
	{
		print_names(option);
		exit(1);
	}
	envi.envi = check_enviroment(envp);
	envi.last_status = 0;
	while (1)
	{
		prompt = create_prompt();
		line = readline(prompt);
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
		check_line(line, &envi);
		free(line);
		free(prompt);
	}
	return (free_env(envi.envi), free(prompt), 0);
}
