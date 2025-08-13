/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:05:20 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/13 11:03:01 by gafreire         ###   ########.fr       */
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
		if (temp->token != T_REDIR_IN
			&& temp->token != T_REDIR_OUT
			&& temp->token != T_PIPE)
        {
			if (temp->kind == T_SQ)
				printf("Se imprime literal -> %s\n",temp->inf);
			else
			{
				if (temp->kind == T_DQ)
					printf("Se expande -> %s\n",temp->inf);
				else if (temp->kind == T_PLAIN)
					printf("Se expande -> %s\n",temp->inf);
			}
            //printf("%s\n",(*temp)->token);
        }
			temp = temp->next;
	}
	return (1);
}