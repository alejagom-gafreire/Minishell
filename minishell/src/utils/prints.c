/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:03:39 by alejogogi         #+#    #+#             */
/*   Updated: 2025/07/30 20:04:30 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
