/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:49:46 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/12 16:49:48 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_env(const void *a, const void *b)
{
	char *const	*str_a;
	char *const	*str_b;

	str_a = (char *const *)a;
	str_b = (char *const *)b;
	return (ft_strcmp(*str_a, *str_b));
}

char	**all_args(char *args)
{
	char	**cpy;

	if (!args)
		return (NULL);
	cpy = ft_split(args, ' ');
	if (!cpy)
		return (NULL);
	return (cpy);
}

int	valid_args(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		return (0);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	print_sorted(t_shell *envp)
{
	char	**sorted;
	char	*print;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (envp->envi[count])
		count++;
	sorted = check_enviroment(envp->envi);
	qsort(sorted, count, sizeof(char *), cmp_env);
	while (i < count)
	{
		print = ft_strchr(sorted[i], '=');
		if (print)
		{
			printf("declare -x %.*s=\"%s\"\n",
				(int)(print - sorted[i]), sorted[i], print + 1);
		}
		else
			printf("declare -x %s\n", sorted[i]);
		i++;
	}
	free_split(sorted);
	return (0);
}
