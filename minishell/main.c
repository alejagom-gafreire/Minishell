/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:09:27 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/21 12:16:46 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argc, char *argv[])
{
    if (argc == 1)
        check_token(argc,argv);
    else
        printf("Esta mal\n");
    return (0);
}