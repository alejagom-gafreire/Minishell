/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-07 16:16:19 by gafreire          #+#    #+#             */
/*   Updated: 2025-09-07 16:16:19 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_argv(char *argv)
{
    int i;

    i = 0;
    while (argv[i] == '+' || argv[i] == '-')
        i++;
    while (argv[i])
    {
        if (!ft_isdigit(argv[i]))
            return (0);
        i++;
    }
    return (1);    
}

int exec_exit(char **argv)
{
    int error_code;

    error_code = 0;
    if (argv[1])
    {
        if (!check_argv(argv[1]))
        {
            printf("error: argument\n"); // write??
            exit(2);
        }
    }
    if (argv[2])
        return(printf("error: too many arguments\n"),1); // write
    error_code = ft_atoi(argv[1]);
    printf("exit mini\n");
    exit(error_code);
    return (0);
}