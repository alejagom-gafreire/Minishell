/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:45 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/30 20:23:18 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_process(t_mini *mini)
{
	//t_parcer *list;

	printf("COMANDOS: %d\n", mini->exec->cmds);
	// (&exec)->infile = NULL;
	// (&exec)->outfile = NULL;
	// list = mini->parcer;
	// while (list)
	// {
	// 	if (list->name_infile)
	// 	{
	// 		(&exec)->infile = open(list->name_infile, O_RDONLY);
	// 		if ((&exec)->infile == -1)
	// 			return ;
	// 	}
	// 	if (list->name_outfile)
	// 	{
	// 		(&exec)->outfile = open(list->name_outfile, O_WRONLY, O_CREAT, 
	// 				O_TRUNC, 0644);
	// 		if ((&exec)->outfile == -1)
	// 			return ;
	// 	}
	// 	create_childs();
	// 	list = list->next;
	// }
}

//contar la cantidad de comandos que hay separados por pipes
//crear un pipe por cada par de comandos
//crear los procesos hijos (fork)
//buscar los comandos en el path
//hacerlos si se le quita las variables de entorno
