/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:48:14 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/22 10:16:37 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_lexer *lexer)
{
	while (lexer)
	{
		printf("Token: %s (tipo %d)\n", lexer->inf, lexer->token);
		lexer = lexer->next;
	}
}

void	add_token(t_lexer **lexer, char *info, tokens type)
{
	t_lexer	*new_lexer;
	t_lexer	*tmp;

	new_lexer = (t_lexer *)malloc(sizeof(t_lexer));
	// inicializar nodo
	new_lexer->next = NULL;
	new_lexer->last = NULL;
	new_lexer->inf = strdup(info); // usar la libft?
	new_lexer->token = type;
	if (*lexer == NULL)
		*lexer = new_lexer; // Si esta la lista vacia
	else
	{
		tmp = *lexer;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_lexer;
		new_lexer->last = tmp;
	}
}

/*
Check the line character by character to find the special operators
*/
void	check_line(char *line) // change type variable
{
	int i;
	t_lexer *lexer_list = NULL;
	i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '|')
			add_token(&lexer_list, "|", T_PIPE);
		else if (line[i] == '<')
		{
			add_token(&lexer_list, "<", T_REDIR_IN);
			// tambien añadir <<
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				add_token(&lexer_list, ">>", T_REDIR_OUT);
				i++;
			}
			else
				add_token(&lexer_list, ">", T_REDIR_OUT);
		}
		// añadir para T_GENERAL
		// printf("%c", line[i]);
		i++;
	}
	printf("\n");
	print_tokens(lexer_list);
}
