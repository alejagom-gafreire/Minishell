/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:43:45 by alejandro         #+#    #+#             */
/*   Updated: 2025/08/29 16:44:11 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Lo separo en dos funciones para que en el ejecutor puedas 
	checkear de manera rapida si es un builtin y si lo es ejecutarlo

	exec_builtins debería devolver el valor del status
*/

void exec_builtins(char *word)
{
	// // char *argv_echo1[] = {"echo", "hola", NULL};
    // char *argv_echo2[] = {"echo", "-nnnnnnnnnnnnnnnnnnnnnnnnn", "hola", NULL};
	// char *argv_cd1[] = {"cd","./include/" ,NULL};
	// char *argv_cd1[] = {"cd","src/lexer", "ey", "tu",NULL};
	// char *argv_cd1[] = {NULL};
	// char *argv_exit[] = {"exit","4563","ey",NULL};
	char *argv_exit[] = {"exit","-12",NULL};

	// if (ft_strcmp(word, "echo") == 0)
	// {
	// 	// exec_echo(argv1);
	// 	exec_echo(argv2);
	// }	
	// if (!ft_strcmp(word, "cd"))
	// 	exec_cd(argv_cd1);
	// else if (!ft_strcmp(builtin, "pwd"))
	// 	exec_pwd(word);// env
	// else if (!ft_strcmp(builtin, "export"))
	// 	exec_export
	// else if (!ft_strcmp(builtin, "unset"))
	// 	exec_unset
	// else if (!ft_strcmp(builtin, "env"))
	// 	exec_env
	if (!ft_strcmp(word, "exit"))
		exec_exit(argv_exit);
}

t_tokens	compare_builtins(char *word)
{
	t_tokens	type;
	// (void)word;
	if (ft_strcmp("cd", word) == 0)
	{
		type = T_BUILTINS;
		exec_builtins(word);
	}
	else if (ft_strcmp("echo", word) == 0)
	{
		type = T_BUILTINS;
		// exec_builtins(word);
	}
	else if (ft_strcmp("pwd", word) == 0)
	{
		type = T_BUILTINS;
		// exec_builtins(word);
	}
	else if (ft_strcmp("export", word) == 0)
		type = T_BUILTINS;
	else if (ft_strcmp("unset", word) == 0)
		type = T_BUILTINS;
	else if (ft_strcmp("env", word) == 0)
		type = T_BUILTINS;
	else if (ft_strcmp("exit", word) == 0)
	{
		type = T_BUILTINS;
		exec_builtins(word);
	}
	else
		type = T_NAME_CMD;
	return (type);
}
// int is_builtin(char *builtin)
// {
// 	if (!ft_strcmp(builtin, "echo"))
// 		return (1);
// 	else if (!ft_strcmp(builtin, "cd"))
// 		return (1);
// 	else if (!ft_strcmp(builtin, "pwd"))
// 		return (1);
// 	else if (!ft_strcmp(builtin, "export"))
// 		return (1);
// 	else if (!ft_strcmp(builtin, "unset"))
// 		return (1);
// 	else if (!ft_strcmp(builtin, "env"))
// 		return (1);
// 	else if (!ft_strcmp(builtin, "exit"))
// 		return (1);
// 	return (0);
// }