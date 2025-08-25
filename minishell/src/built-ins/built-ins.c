/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-23 15:31:29 by gafreire          #+#    #+#             */
/*   Updated: 2025-08-23 15:31:29 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Lo separo en dos funciones para que en el ejecutor puedas 
	checkear de manera rapida si es un builtin y si lo es ejecutarlo

	exec_builtins debería devolver el valor del status
*/

void exec_builtins(char *builtin)
{

	if (!ft_strcmp(builtin, "echo"))
		exec_echo();	
	// else if (!ft_strcmp(builtin, "cd"))
		// exec_cd
	// else if (!ft_strcmp(builtin, "pwd"))
		//exec_pwd
	// else if (!ft_strcmp(builtin, "export"))
		//exec_export
	// else if (!ft_strcmp(builtin, "unset"))
		//exec_unset
	// else if (!ft_strcmp(builtin, "env"))
		//exec_env
	// else if (!ft_strcmp(builtin, "exit"))
		//exec_exit
}

int is_builtin(char *builtin)
{
	if (!ft_strcmp(builtin, "echo"))
		return (1);
	else if (!ft_strcmp(builtin, "cd"))
		return (1);
	else if (!ft_strcmp(builtin, "pwd"))
		return (1);
	else if (!ft_strcmp(builtin, "export"))
		return (1);
	else if (!ft_strcmp(builtin, "unset"))
		return (1);
	else if (!ft_strcmp(builtin, "env"))
		return (1);
	else if (!ft_strcmp(builtin, "exit"))
		return (1);
	return (0);
}
