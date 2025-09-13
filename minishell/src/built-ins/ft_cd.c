/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 08:22:57 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-04 08:22:57 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME", 4) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

int	exec_cd(char **cmd, t_shell *envp) // char **argv, t_env *env
{
	// argv[0] = "cd"
	// argv[1] = ruta (debe existir)
	// env = nuestro env/ tiene que estar el pwd

	int resultado;
    char *target;
    int nbr;

	(void)envp;
	if (!cmd[1])
	{
		target =  get_path(envp->envi); //getenv("HOME"); // cambiar por el nuestro
		resultado = chdir(target);
		return (0);
	}
	else
	{
		// validar el numero de argumentos
		nbr = get_size(cmd);
		if (nbr == 0)
			return (printf("cd:missing argument\n"),1);
		else if (nbr > 2)
			return (printf("cd:too many arguments\n"),1);
		// char *ruta = argv[1];
		// char *oldpwd = &ruta;
		// cambiar directorio

		resultado = chdir(cmd[1]);
		if (resultado == -1)
			return (printf("cd"),1);
	}
	// char *nueva = getcwd(NULL,0);
	// if (nueva == NULL)
	// {
	//     printf("cd");
	//     return(1);
	// }

	//  actualizar variables de entorno
	// if (oldpwd != NULL)
	//     set_env(entorno,"OLDPWD",oldpwd)
	//    set_env(entorno,"PWD",nueva)

	// free(nueva);
	return (0);
}
