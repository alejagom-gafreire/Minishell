/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:48:14 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/23 12:09:08 by gafreire         ###   ########.fr       */
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
Comprobar linea por linea para detectar todos los tokens
*/
void	check_line(char *line) // cambiar el tipo de variable/ posiblemente
{
	int i;
	t_lexer *lexer_list = NULL;
	int first_word = 1;
	tokens last_token = T_GENERAL;
	i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			i++;
		}
		else if (line[i] == '|')
		{
			add_token(&lexer_list, "|", T_PIPE);
			last_token = T_PIPE;
			first_word = 1; // despues de un pipe siempre viene un comando
			i++;
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
			{
				add_token(&lexer_list, "<<", T_REDIR_IN);
				last_token = T_REDIR_IN;
				i += 2;
			}
			else
			{
				add_token(&lexer_list, "<", T_REDIR_IN);
				last_token = T_REDIR_IN;
				i++;
			}
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				add_token(&lexer_list, ">>", T_REDIR_OUT);
				last_token = T_REDIR_OUT;
				i += 2;
			}
			else
			{
				add_token(&lexer_list, ">", T_REDIR_OUT);
				last_token = T_REDIR_OUT;
				i++;
			}
		}
		// si esta en comillas simples
		else if (line[i] == '\'')
		{
			int start = check_simple_quotes(line,i); // compruebo si esta entre dos comillas simples
			char *word_quotes = strndup(&line[i + 1], start - (i + 1)); // duplico la frase
			add_token(&lexer_list, word_quotes, T_GENERAL); 
			i = start;
			i++;
		}
		// si esta en comillas dobles
		else if (line[i] == '"')
		{
			int start = check_double_quotes(line,i);  // compruebo si esta entre dos comillas dobles
			char *word_quotes = strndup(&line[i + 1], start - (i + 1)); // duplico la frase
			add_token(&lexer_list, word_quotes, T_GENERAL);
			i = start;
			i++;
		}
		// si es una palabra
		else
		{
			int start = i;
			while (line[i] != '\0' && line[i] != ' ' && line[i] != '<'
				&& line[i] != '>' && line[i] != '|')
				i++;
			if (i > start)
			{
				char *word = strndup(&line[start], i - start); // cambiar por ft_substr de la libft??
				
				if (last_token == T_REDIR_IN) // Si viene de <,entonces T_INFILE
				{
					add_token(&lexer_list, word, T_INFILE);
					last_token = T_INFILE;
				}
				else if (last_token == T_REDIR_OUT) // Si viene de > o >> entonces T_OUTFILE
				{
					add_token(&lexer_list, word, T_OUTFILE);
					last_token = T_OUTFILE;
				}
				else if (first_word) // Si es la primera palabra
				{
					add_token(&lexer_list, word, T_NAME_CMD);
					last_token = T_NAME_CMD;
				}
				else
				{
					add_token(&lexer_list, word, T_NAME_CMD);
					last_token = T_NAME_CMD;
				}
				first_word = 0;
			}
		}
	}
	print_tokens(lexer_list);
}  