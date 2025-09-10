/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:43:45 by alejandro         #+#    #+#             */
/*   Updated: 2025/08/29 16:44:11 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_env(const void *a, const void *b)
{
	char * const *str_a;
	char * const *str_b;

	str_a = (char * const *)a;
	str_b = (char * const *)b;
	return (ft_strcmp(*str_a, *str_b));
}

int	print_sorted(t_shell *envp)
{
	char	**sorted;
	char	*print;
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (envp->envi[count])
		count++;
	sorted = check_enviroment(envp->envi);
	if (!sorted)
		return (1);
	qsort(sorted, count, sizeof(char *), cmp_env);
	while (i < count)
	{
		print = ft_strchr(sorted[i], '=');
		if (print)
		{
			printf("declare -x %.*s=\"%s\"\n", (int)(print - sorted[i]), sorted[i], print + 1);
		}
		else
			printf("declare -x %s\n", sorted[i]);
		i++;
	}
	free(sorted);
	return (0);
}

int	valid_args(t_parcer *list)
{
	int	i;

	i = 0;
	if (list->arg_export || (!ft_isalpha(list->arg_export) && list->arg_export[0] != '_'))
		return (0);
	while (list->arg_export[i] && list->arg_export[i] != '=')
	{
		if (!ft_isalnum(list->arg_export[i]) && list->arg_export[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	add_update_env(char *arg, char **envi)
{
	int	i;
	char	*equal;
	size_t	key_len;

	equal = ft_strchr((const char *)arg, '=');
	if (!equal)
		key_len = equal - arg;
	else
		key_len = ft_strlen(arg);
	i = 0;
	while (*envi[i])
	{
		if (!ft_strncmp(((*env)[i], arg, key_len));
	}

}

int	ft_export(t_shell *envp, t_parcer *list)
{
	if (list->next == NULL)
		return (print_sorted(envp));
	else
	{
		list = list->next;
		while (list)
		{
			if (list->arg_export)
			{
				if (!valid_args(list))
				{
					printf("export: `%s': not a valid identifier\n", list->arg_export);
					return(1);
				}	
				else
					add_update_env(list, envp->envi);
			}
			list = list->next;
		}
		return (0);
	}
}

// int ft_export(char **args, t_shell *envp)
// {
//     int i = 1; // args[0] = "export"
    
//     if (!args[i])
//         return print_sorted_env(envp);

//     while (args[i])
//     {
//         if (!valid_identifier(args[i]))
//         {
//             fprintf(stderr, "export: `%s': not a valid identifier\n", args[i]);
//             envp->last_status = 1;
//         }
//         else
//         {
//             add_or_update_env(args[i], envp);
//         }
//         i++;
//     }
//     return 0;
// }

int	cmp_env(const void *a, const void *b)
{
	char * const *str_a;
	char * const *str_b;

	str_a = (char * const *)a;
	str_b = (char * const *)b;
	return (ft_strcmp(*str_a, *str_b));
}

int	print_sorted(t_shell *envp)
{
	char	**sorted;
	char	*print;
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (envp->envi[count])
		count++;
	sorted = check_enviroment(envp->envi);
	if (!sorted)
		return (1);
	qsort(sorted, count, sizeof(char *), cmp_env);
	while (i < count)
	{
		print = ft_strchr(sorted[i], '=');
		if (print)
		{
			printf("declare -x %.*s=\"%s\"\n", (int)(print - sorted[i]), sorted[i], print + 1);
		}
		else
			printf("declare -x %s\n", sorted[i]);
		i++;
	}
	free(sorted);
	return (0);
}

int	valid_args(t_parcer *list)
{
	int	i;

	i = 0;
	if (list->arg_export || (!ft_isalpha(list->arg_export) && list->arg_export[0] != '_'))
		return (0);
	while (list->arg_export[i] && list->arg_export[i] != '=')
	{
		if (!ft_isalnum(list->arg_export[i]) && list->arg_export[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	add_update_env(t_parcer *list, char **envi)
{
	// hay que hacer una copia del env, para no depender del original
	// buscar en el env si ya existe para reemplazar el que existe
	// hacer realloc para no gatar memoria inceseariamente
	// agregar los nuevos en caso de que no exitan
}

int	ft_export(t_shell *envp, t_parcer *list)
{
	if (list->next == NULL)
		return (print_sorted(envp));
	else
	{
		list = list->next;
		while (list)
		{
			if (list->arg_export)
			{
				if (!valid_args(list))
				{
					printf("export: `%s': not a valid identifier\n", list->arg_export);
					return(1);
				}	
				else
					add_update_env(list->arg_export, envp->envi);
			}
			list = list->next;
		}
		return (0);
	}
}

int	exec_buildings(t_parcer *list,char **argv, t_shell *envp)
{
	if (ft_strcmp("env", list->building) == 0)
		return (exec_env(envp));
	else if (ft_strcmp("cd", list->building) == 0)
		return (exec_cd(argv,envp));
	else if (ft_strcmp("echo", list->building) == 0)
		return (exec_echo(argv));
	else if (ft_strcmp("pwd", list->building) == 0)
		return (exec_pwd());
	// else if (ft_strcmp("export", list->building) == 0)
	// 	return (ft_export());
	// else if (ft_strcmp("unset", list->building) == 0)
	// 	return (ft_unset());
	else if (ft_strcmp("exit", list->building) == 0)
		return (exec_exit(argv));
	return (0);
}

t_tokens	compare_buildings(char *word)
{
	t_tokens	type;

	(void)word;
	if (ft_strcmp("cd", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("echo", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("env", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("pwd", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("export", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("unset", word) == 0)
		type = T_BUILDINGS;
	else if (ft_strcmp("exit", word) == 0)
		type = T_BUILDINGS;
	else
	    type = T_NAME_CMD;
	return (type);
}
