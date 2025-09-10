/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-01 12:09:08 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-01 12:09:08 by gafreire         ###   ########gafreire  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// env
int	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd"); // printf ?? o no
		return (1);// status
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
