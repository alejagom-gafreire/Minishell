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

int	cmp_env(const void *a, const void *b)
{
	char *const	*str_a;
	char *const	*str_b;

	str_a = (char *const *)a;
	str_b = (char *const *)b;
	return (ft_strcmp(*str_a, *str_b));
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

int	cmp_env_key(const char *env, const char *arg, size_t key_len)
{
	if (ft_strncmp(env, arg, key_len) == 0 &&
		(env[key_len] == '=' || env[key_len] == '\0'))
	{
		return (1);
	}
	return (0);
}

void	add_update_env(char *arg, char ***envi)
{
	int		i;
	char	*equal;
	char	**cpy_envi;
	size_t	key_len;

	equal = ft_strchr(arg, '=');
	if (equal)
		key_len = equal - arg;
	else
		key_len = ft_strlen(arg);
	i = 0;
	while ((*envi)[i])
	{
		if (cmp_env_key((*envi)[i], arg, key_len))
		{
			if ((equal))
			{
				free((*envi)[i]);
				(*envi)[i] = ft_strdup(arg);
			}
			return ;
		}
		i++;
	}
	cpy_envi = malloc(sizeof (char *) * (i + 2));
	if (!cpy_envi)
		return ;
	i = 0;
	while ((*envi)[i])
	{
		cpy_envi[i] = (*envi)[i];
		i++;
	}
	cpy_envi[i] = ft_strdup(arg);
	cpy_envi[i + 1] = NULL;
	free(*envi);
	*envi = cpy_envi;
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

int	ft_export(t_shell *envp, t_parcer *list)
{
	char	**aux;
	char	**temp;

	if (list->arg_export == NULL && list->building && list->cmd_args == NULL)
		return (print_sorted(envp));
	aux = all_args(list->cmd_args);
	temp = aux;
	while (*temp)
	{
		if (!valid_args(*temp))
		{
			printf("export: `%s': not a valid identifier\n", *temp);
			return (1);
		}
		else
			add_update_env(*temp, &envp->envi);
		temp++;
	}
	free_split(aux);
	return (0);
}
