/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-10 10:02:23 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-10 10:02:23 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_shell *envp, t_parcer *list)
{
	int	i;

	if (list->argv[1])
	{
		printf("env: «%s»: No existe el archivo o el directorio\n",
				list->argv[1]);
		return (1);
	}
	if (list->cmd_args || ft_strcmp(list->builtin, "cd") == 0)
	{
		if (list->cmd_args)
		{
			printf("env: «%s»: No existe el archivo o el directorio\n",
				list->cmd_args);
			return (1);
		}
	}
	i = 0;
	while (envp->envi[i] != NULL)
	{
		printf("%s\n", envp->envi[i]);
		i++;
	}
	return (0);
}
