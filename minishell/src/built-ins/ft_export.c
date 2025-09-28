/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:29:21 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/11 18:29:26 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**safe_malloc(int i, char ***envi, char *arg)
{
	char	**cpy_envi;

	cpy_envi = malloc(sizeof(char *) * (i + 2));
	if (!cpy_envi)
		return (NULL);
	i = 0;
	while ((*envi)[i])
	{
		cpy_envi[i] = (*envi)[i];
		i++;
	}
	cpy_envi[i] = ft_strdup(arg);
	cpy_envi[i + 1] = NULL;
	return (cpy_envi);
}

size_t	len_equal(char **equal, char *arg)
{
	size_t	key_len;

	*equal = ft_strchr(arg, '=');
	if (*equal)
		key_len = *equal - arg;
	else
		key_len = ft_strlen(arg);
	return (key_len);
}

static int	same_key(const char *a, const char *b)
{
	size_t	i;

	i = 0;
	while (a[i] && a[i] != '=' && b[i] && b[i] != '=')
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}

void	add_update_env(char *arg, char ***envi)
{
	char	**env;
	int		i;
	char	*dup;
	char	**newv;

	env = *envi;
	if (!arg)
		return ;
	i = 0;
	while (env && env[i])
	{
		if (same_key(arg, env[i]))
		{
			dup = ft_strdup(arg);
			if (!dup)
				return ;
			free(env[i]);
			env[i] = dup;
			return ;
		}
		i++;
	}
	newv = safe_malloc(i, &env, arg);
	free(env);
	*envi = newv;
}

int	ft_export(t_shell *envp, t_parcer *list)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!list->argv || !list->argv[1])
		return (print_sorted(envp));
	while (list->argv[i])
	{
		if (!valid_args(list->argv[i]))
		{
			printf("export: `%s': not a valid identifier\n", list->argv[i]);
			status = 1;
		}
		else
			add_update_env(list->argv[i], &envp->envi);
		i++;
	}
	return (status);
}
