/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:48:14 by gafreire          #+#    #+#             */
/*   Updated: 2025/07/25 15:59:58 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_lexer **lexer_list, int *last_token, int *first_word)
{
	add_token(lexer_list, "|", T_PIPE);
	*last_token = T_PIPE;
	*first_word = 1;
}

void	print_parcer(t_parcer *parcer)
{
	while (parcer)
	{
		printf("voy aqui\n");
		printf("cmd: %s (infile; %s) (outfile; %s)\n", parcer->cmd_args,
			parcer->name_infile, parcer->name_outfile);
		parcer = parcer->next;
	}
}

void	print_tokens(t_lexer *lexer)
{
	while (lexer)
	{
		printf("Token: %s (tipo %d)\n", lexer->inf, lexer->token);
		lexer = lexer->next;
	}
}

void	add_token(t_lexer **lexer, char *info, t_tokens type)
{
	t_lexer	*new_lexer;
	t_lexer	*tmp;

	new_lexer = (t_lexer *)malloc(sizeof(t_lexer));
	new_lexer->next = NULL;
	new_lexer->last = NULL;
	new_lexer->inf = ft_strdup(info);
	new_lexer->token = type;
	if (*lexer == NULL)
		*lexer = new_lexer;
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

t_lexer	*aux_line(char *line, t_mini *mini)
{
	t_lexer *list;
	int 	i;
	int	first_word;
	int 	last_token;

	list = NULL;
	first_word = 1;
	t_last_token = T_GENERAL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '|')
		{
			handle_pipe(&list, &last_token, &first_word);
			i++;
		}
		else if (line[i] == '<')
			i = handle_input_redirect(line, i, &list, &last_token);
		else if (line[i] == '>')
			i = handle_output_redirect(line, i, &list, &last_token);
		else if (line[i] == '\'')
			i = handle_simple_quotes(line, i, &list);
		else if (line[i] == '"')
			i = handle_double_quotes(line, i, &list);
		else
			i = handle_word(line, i, &list, &last_token, &first_word);
	}
	return(list);
}

void	check_line(char *line)
{
	int			i;
	t_mini			*mini;
	int			first_word;
	int			last_token;

	mini = NULL;
	first_word = 1;
	last_token = T_GENERAL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '|')
		{
			handle_pipe(&lexer_list, &last_token, &first_word);
			i++;
		}
		else if (line[i] == '<')
			i = handle_input_redirect(line, i, &lexer_list, &last_token);
		else if (line[i] == '>')
			i = handle_output_redirect(line, i, &lexer_list, &last_token);
		else if (line[i] == '\'')
			i = handle_simple_quotes(line, i, &lexer_list);
		else if (line[i] == '"')
			i = handle_double_quotes(line, i, &lexer_list);
		else
			i = handle_word(line, i, &lexer_list, &last_token, &first_word);
	}
	add_parcer(lexer_list, &parcer);
	// añadir para T_NAME_CMD Acces??
	// añadir para T_INFILE
	// añadir para T_OUTFILE
	// añadir para T_GENERAL
	// printf("%c", line[i]);
	printf("\n");
	print_tokens(lexer_list);
	printf("\n");
	print_parcer(parcer);
}
