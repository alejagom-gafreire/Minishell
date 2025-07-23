/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:18:03 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/22 21:48:29 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inside_parcer(t_parcer **head, t_parcer *new_node)
{
	t_parcer *tmp;

	printf("añadiendo nodo\n");
	if (!head || !new_node)
		return;
	if (*head == NULL)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}


static t_parcer	*mem_parcer(void)
{
	t_parcer *parcer;

	parcer = malloc(sizeof(t_parcer));
	if (!parcer)
		return(NULL);
	parcer->next = NULL;
	parcer->cmd_args = NULL;
	parcer->name_infile = NULL;
	parcer->name_outfile = NULL;
	return(parcer);
}

// void	add_parcer(t_lexer *lexer, t_parcer **parcer)
// {
// 	t_lexer *aux = lexer;
// 	t_parcer *new_parcer;
// 	char	*cmd = NULL;
// 	int	i = 0;

// 	while (aux->next != NULL)
// 	{
// 		i = 0;
// 		if (aux->token == T_REDIR_IN || aux->token == T_PIPE)
// 			aux = aux->next;
// 		new_parcer = mem_parcer();
// 		while (aux && aux && aux->next->token != T_PIPE)
// 		{
// 			if (aux->token == T_INFILE)
// 				 new_parcer->name_infile = ft_strdup(aux->inf);
// 			else if (aux->token == T_NAME_CMD && i == 0)
// 			{
// 				i = 1;
// 				if (aux->next->token == T_NAME_CMD)
// 				{
// 					cmd = ft_strjoin(aux->inf, aux->next->inf);
// 					new_parcer->cmd_args = ft_strdup(cmd);
// 				}
// 				else
// 					new_parcer->cmd_args = ft_strdup(aux->inf);
// 			}
// 			else if (aux->token == T_OUTFILE)
// 				new_parcer->name_outfile = ft_strdup(aux->inf);
// 			aux = aux->next;
// 		}
// 		free(cmd);
// 		inside_parcer(&(*parcer), new_parcer);
// 		aux = aux->next;
// 	}
// }

void	add_parcer(t_lexer *lexer, t_parcer **parcer)
{
	t_lexer		*aux = lexer;
	t_parcer	*new_parcer;
	char		*cmd = NULL;
	char		*tmp = NULL;
	
	while (aux && aux->next != NULL)
	{
		if (aux->token == T_REDIR_IN || aux->token == T_PIPE)
			aux = aux->next;
		new_parcer = mem_parcer();
		if (!new_parcer)
			return ;

		while (aux && aux->next && aux->next->token != T_PIPE)
		{
			if (aux->token == T_INFILE)
				new_parcer->name_infile = ft_strdup(aux->inf);
			else if (aux->token == T_NAME_CMD)
			{
				printf("lexer tiene esto: %s\n", aux->inf);
				printf("lexer tiene esto: %d\n", aux->next->token);
				if (aux->next && aux->next->token == T_GENERAL) //verificar bien los enum error en los tipos!
				{
					tmp = ft_strjoin(aux->inf, " ");
					cmd = ft_strjoin(aux->next->inf, tmp);
					//free(tmp);
					new_parcer->cmd_args = cmd;
					printf("cmd arrojo esto: %s\n", new_parcer->cmd_args);
					//free(cmd);
					aux = aux->next;
				}
				else
					new_parcer->cmd_args = ft_strdup(aux->inf);
			}
			else if (aux->token == T_OUTFILE)
				new_parcer->name_outfile = ft_strdup(aux->inf);
			aux = aux->next;
		}
		if (cmd)
			free(cmd);

		inside_parcer(parcer, new_parcer);

		if (aux)
			aux = aux->next;
	}
}
