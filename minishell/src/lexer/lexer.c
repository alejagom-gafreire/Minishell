/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:48:14 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/15 13:06:04 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_lexer **lexer_list, int *first_word)
{
	add_token(lexer_list, "|", T_PIPE, T_PLAIN);
	(*lexer_list)->last_token = T_PIPE;
	*first_word = 1;
}

void	add_token(t_lexer **lexer, char *info, t_tokens type, t_kind kind)
{
	t_lexer	*new_lexer;
	t_lexer	*tmp;

	new_lexer = (t_lexer *)malloc(sizeof(t_lexer));
	new_lexer->next = NULL;
	new_lexer->last = NULL;
	new_lexer->inf = ft_strdup(info);
	new_lexer->token = type;
	new_lexer->last_token = type;
	new_lexer->kind = kind;
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

t_lexer	*aux_line(char *line)
{
	t_lexer	*list;
	int		i;
	int		first_word;

	list = NULL;
	first_word = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			i = check_redirect(line, i, &list, &first_word);
		else if (line[i] == '\'' || line[i] == '"')
		{
			i = check_quotes(line, i, &list);
			if (i < 0)
				return (free_lexer(list), NULL);
		}
		else
			i = handle_word(line, i, &list, &first_word);
	}
	return (list);
}

void	check_line(char *line, t_shell *envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return ;
	mini->lexer = aux_line(line);
	if (!mini->lexer)
		return ;
	if (expand_tokens(&mini->lexer, envp->last_status) != 0)
		return ;
	mini->parcer = add_parcer(mini->lexer);
	num_comands(mini);
	execute_cmd(mini, envp);
	free_minishell(mini);
}

/*
	printf("last status %d\n", envp->last_status);
	printf("\n");
	print_tokens(mini->lexer);
	printf("\n");
	print_parcer(mini->parcer);

	t_lexer	*pru = mini->lexer;
	while (pru != NULL)
	{
		printf("lista lexer: %s\n", pru->inf);
		pru = pru->next;
	}
*/
