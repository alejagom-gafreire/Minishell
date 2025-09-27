/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:00:23 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/30 17:26:35 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*next_node(t_lexer *aux)
{
	while (aux && (aux->token != T_PIPE || aux->token == T_DELIM))
		aux = aux->next;
	if (!aux)
		return (NULL);
	return (aux->next);
}

t_lexer	*aux_redir_in(t_lexer *aux, t_parcer *new_parcer)
{
	if (aux && aux->next && aux->next->token == T_INFILE)
		aux = aux->next;
	else
	{
		print_error_syntax();
		new_parcer->syntax_error = 1;
		aux = NULL;
	}
	return (aux);
}

t_lexer	*aux_redir_out(t_lexer *aux, t_parcer *new_parcer, t_shell **env)
{
	if (aux && aux->next)
		return (handle_outfile(aux, new_parcer, env));
	print_error_syntax();
	new_parcer->syntax_error = 1;
	return (NULL);
}

int	open_outfile(t_lexer *file, int appened, t_shell **env)
{
	int	fd;

	fd = -1;
	if (appened)
	{
		fd = open(file->inf, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
		{
			(*env)->denied_open = 1;
			return (-1);
		}
	}
	else
	{
		fd = open(file->inf, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			(*env)->denied_open = 1;
			return (-1);
		}
	}
	return (fd);
}

void	inside_parcer(t_parcer **head, t_parcer *new_node)
{
	t_parcer	*tmp;

	if (!head || !new_node)
		return ;
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
