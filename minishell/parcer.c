/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:18:03 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/23 22:11:43 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inside_parcer(t_parcer **head, t_parcer *new_node)
{
	t_parcer *tmp;

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

void add_parcer(t_lexer *lexer, t_parcer **parcer)
{
	t_lexer		*aux = lexer;
	t_parcer	*new_parcer;
	char		*cmd;
	char		*tmp;

	while (aux)
	{
		new_parcer = mem_parcer(); //creo nuevo nodo.
		if (!new_parcer)
			return ;
		cmd = NULL;
		while (aux && aux->token != T_PIPE) //lo separo verificando que no sea pipe.
		{
			if (aux->token == T_REDIR_IN) //avanzo en redirecciones.
				aux = aux->next;			
			if (aux && aux->token == T_INFILE)
				new_parcer->name_infile = ft_strdup(aux->inf);
			else if (aux && aux->token == T_OUTFILE)
					new_parcer->name_outfile = ft_strdup(aux->inf);
			else if (aux->token == T_NAME_CMD)
			{
				if (!cmd)
					cmd = ft_strdup(aux->inf);
				else
				{
					tmp = ft_strjoin(cmd, " ");
					free(cmd);
					cmd = ft_strjoin(tmp, aux->inf); //ya tiene el siguiente comando :)
					free(tmp);
				}
			}
			aux = aux->next; //recorro el nodo en caso de "grep -e -e" cmd + tmp todo el rato hasta el pipe.
		}
		if (cmd)
		{
			new_parcer->cmd_args = ft_strdup(cmd);
			free(cmd);
		}
		inside_parcer(parcer, new_parcer); //agrego el nodo.
		if (aux && aux->token == T_PIPE)
			aux = aux->next; // salto el pipe cuando lo encuentro.
	}
}

