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

int	cmp_env_key(const char *env, const char *arg, size_t key_len)
{
	if (ft_strncmp(env, arg, key_len) == 0
		&& (env[key_len] == '=' || env[key_len] == '\0'))
	{
		return (1);
	}
	return (0);
}

static char	**safe_malloc(int i, char ***envi, char *arg)
{
	char	**cpy_envi;

	cpy_envi = malloc(sizeof (char *) * (i + 2));
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

void	add_update_env(char *arg, char ***envi)
{
	int		i;
	char	*equal;
	char	**cpy_envi;
	size_t	key_len;

	key_len = len_equal(&equal, arg);
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
	cpy_envi = safe_malloc(i, &(*envi), arg);
	free(*envi);
	*envi = cpy_envi;
}

int	ft_export(t_shell *envp, t_parcer *list)
{
	char	**aux;
	char	**temp;
	int		status;

	status = 0;
	if (list->arg_export == NULL && list->building && list->cmd_args == NULL)
		return (print_sorted(envp));
	aux = all_args(list->cmd_args);
	temp = aux;
	while (*temp)
	{
		if (!valid_args(*temp))
		{
			printf("export: `%s': not a valid identifier\n", *temp);
			status = 1;
		}
		else
			add_update_env(*temp, &envp->envi);
		temp++;
	}
	free_split(aux);
	if (status == 1)
		return (1);
	else
		return (0);
}
