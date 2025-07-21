/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:48:14 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/21 19:14:28 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
Check the line character by character to find the special operators
*/
void	check_line(char *line) // change type variable
{
	int i;
    Tokens res;
	i = 0;

	while (line[i] != '\0')
	{
        if (line[i] == '|')
            aux_inside_inf(line[i], T_PIPE)
        else if (line[i] == '<')
        {
            aux_inside_inf(line[i], T_REDIR_IN);
		    printf("Encontre un: %c\n", line[i]);
        }
        else if (line[i] == '>')
        {
            if (line[i + 1] == '>')
            {
		        printf("Encontre uno doble: %c%c\n", line[i],line[i + 1]);
                i++;
            }
            else
		        printf("Encontre uno simple: %c\n", line[i]);
                
        }
        char *grep = "grep"
        if ()
		// printf("%c", line[i]); 
		i++;
	}
	printf("\n");
}
