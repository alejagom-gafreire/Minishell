/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:05:20 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/13 17:37:32 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_tokens(t_lexer **lexer_list, char **envp)
{
	t_lexer *temp;

	temp = (*lexer_list);

	(void)envp;
	while (temp)
	{
		if (temp->token != T_REDIR_IN && temp->token != T_REDIR_OUT
			&& temp->token != T_PIPE)
		{
			if (temp->kind == T_SQ)
				printf("Se imprime literal -> %s\n", temp->inf);
			else
			{
				if (temp->kind == T_DQ)
				{
					int i = ft_strlen(temp->inf);
					int z = 0;
					char *prueba = malloc(sizeof(ft_strlen(temp->inf)));
					while (z < i && temp->inf[z] != '$')
						z++;
					printf("TAMAÑO PAPI%d\n",z);
					while (z < i && temp->inf[z] != '\0')
					{
						int x = 0;
						prueba[x] = temp->inf[z];
						x++;
						z++;
					}
					printf("Se expande ->%s\n", prueba);
				}
				// printf("Se expande -> %s\n",temp->inf);
				else if (temp->kind == T_PLAIN)
					printf("Se expande -> %s\n", temp->inf);
			}
			// printf("%s\n",(*temp)->token);
			//getenv()
		}
		temp = temp->next;
	}
	return (1);
}