/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:20:50 by alejogogi         #+#    #+#             */
/*   Updated: 2025/08/03 19:21:45 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_split(char **split)
// {
// 	int	i;

// 	i = 0;
// 	if (!split)
// 		return ;
// 	while (split[i])
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// }

// char	*get_path_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 			return (envp[i] + 5);
// 		i++;
// 	}
// 	return (NULL);
// }

// char *check_absolute_path(char *cmd)
// {
//     if (ft_strchr(cmd, '/'))
//     {
//         if (access(cmd, X_OK) == 0)
//             return (ft_strdup(cmd));    
//         return (NULL);
//     }
//     return (NULL);
// }

// char	*find_executable(char *cmd, char **envp, t_execute *exec)
// {
// 	char	**paths;
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	exec->abs_path = check_absolute_path(cmd);
// 	printf("en esta parte no imprime nada\n");
// 	if (exec->abs_path)
// 		return (exec->abs_path);
// 	exec->path_env = get_path_env(envp);
// 	printf("PATH = %s\n", exec->path_env);
// 	if (!exec->path_env){
// 		printf("hola\n");
// 		return (NULL);
// 	}
// 	printf("voy aqui find execute\n");
// 	paths = ft_split(exec->path_env, ':');
// 	for (int j=0; paths[j]; j++)
//     	printf("paths[%d] = %s\n", j, paths[j]);
// 	while (paths[i])
// 	{
// 		temp = ft_strjoin(paths[i], "/");
// 		exec->full_path = ft_strjoin(temp, cmd);
// 		free(temp);
// 		if (access(exec->full_path, X_OK) == 0)
// 			return (free_split(paths), exec->full_path);
// 		free(exec->full_path);
// 		i++;
// 	}
// 	return (free_split(paths), NULL);
// }
