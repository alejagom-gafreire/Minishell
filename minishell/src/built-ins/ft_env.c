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

int	exec_env(t_shell *envp)
{
	int	i;

	i = 0;
	while (envp->envi[i] != NULL)
	{
		printf("%s\n", envp->envi[i]);
		i++;
	}
	return (0);
}
