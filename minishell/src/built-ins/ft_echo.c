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
    echo consiste en imprimir los parametros que se le envien
    tenemos que tener en cuenta la flag que tiene echo mientras la 
    flag solo sea n sirve pero en el momento que encuentre un caracter diferente
    se imprime tal cual con salto de línea
*/
// int check_flag(char *argv)
// {
//     int i;
//     int flag;

//     i = 1;
//     flag = 0;

//     while(argv[i] != '\0')
//     {
//         if (argv[i] != 'n')
//             return (0);
//         i++;
//     }
//     return (1);
// }

// int	exec_echo(char *argv)
// {
//     int no_flag;

//     no_flag = 1;
//     while (ft_strcmp(argv,"-n") == 0 && check_flag(argv))
//     {
//         // no_flag = 0;
//         //argv++;
//     }

//     if (no_flag)
//         printf("argv\n");
//     else
//         printf("argv");

//     return (1);
// }