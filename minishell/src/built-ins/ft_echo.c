/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 09:49:46 by gafreire          #+#    #+#             */
/*   Updated: 2025-08-25 09:49:46 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	echo consists of printing the parameters passed to it.
	We need to take into account the flag that echo accepts.
	As long as the flag is only 'n' it is valid, but the moment
	a different character is found it is printed as-is, followed
	by a newline.
*/
int	check_flag(char *argv)
{
	int	i;

	if (!argv || argv[0] != '-' || argv[1] != 'n')
		return (0);
	i = 1;
	while (argv[i] != '\0')
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	exec_echo(char **cmd)
{
	int	no_flag;
	int	i;

	no_flag = 0;
	i = 1;
	while (cmd[i] && check_flag(cmd[i]))
	{
		no_flag = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!no_flag)
		printf("\n");
	return (0);
}
