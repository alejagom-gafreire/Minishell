/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:34:27 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/12 15:34:30 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env(char *arg, char ***envi)
{
	char	*equal;
	int		i;
	size_t	key_len;

	key_len = len_equal(&equal, arg);
	i = 0;
	while ((*envi)[i])
	{
		if (cmp_env_key((*envi)[i], arg, key_len))
		{
			free((*envi)[i]);
			while ((*envi)[i + 1])
			{
				(*envi)[i] = (*envi)[i + 1];
				i++;
			}
			(*envi)[i] = NULL;
			return ;
		}
		i++;
	}
}

int	ft_unset(t_shell *envi, t_parcer *list)
{
	char	**aux;
	char	**temp;
	int		status;

	status = 0;
	if (!list->argv)
		return (1);
	aux = all_args(list->argv);
	temp = aux;
	while (*temp)
	{
		if (!valid_args(*temp))
		{
			printf("export: `%s': not a valid identifier\n", *temp);
			status = 1;
		}
		else
			remove_env(*temp, &envi->envi);
		temp++;
	}
	free_split(aux);
	if (status == 1)
		return (1);
	else
		return (0);
}
