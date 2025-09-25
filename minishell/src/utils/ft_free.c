/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:29:11 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/06 16:57:16 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void free_argv(t_parcer *cmd) {
//     int i = 0;
//     if (!cmd || !cmd->argv) return;
//     while (cmd->argv[i]) free(cmd->argv[i++]);  // libera los ft_strdup()
//     free(cmd->argv);                             // libera la matriz (24 bytes)
//     cmd->argv = NULL;
//     cmd->argc = 0;
// }

// void free_parcer_node(t_parcer *n) {
//     if (!n) return;
//     if (n->infile >= 0) { close(n->infile); n->infile = -1; }
//     if (n->outfile >= 0){ close(n->outfile); n->outfile = -1; }
//     free_argv(n);
//     // libera duplicados sueltos si los haces:
//     if (n->builtin && (!n->argv || n->builtin != n->argv[0])) free(n->builtin);
//     free(n->cmd_args);
//     free(n->arg_export);
//     free(n->name_infile);
//     free(n->name_outfile);
//     free(n);
// }

// void free_parcer_list(t_parcer *head) {
//     t_parcer *next;
//     while (head) { next = head->next; free_parcer_node(head); head = next; }
// }

// void free_lexer_list(t_lexer *lx) {
//     while (lx) { t_lexer *nx = lx->next; free(lx->inf); free(lx); lx = nx; }
// }

// void free_after_line(t_mini *mini) {
//     if (!mini) return;
//     if (mini->parcer) { free_parcer_list(mini->parcer); mini->parcer = NULL; }
//     if (mini->lexer)  { free_lexer_list(mini->lexer);   mini->lexer  = NULL; }
//     mini->num_cmd = 0;
// }

// void free_env(char **envi) 
// {
//     if (!envi) 
// 		return; 
// 	for (int i=0; envi[i]; ++i)
// 	{
// 		free(envi[i]); 
// 		free(envi);
// 	}
// }


void	free_lexer(t_lexer *lexer)
{
	t_lexer	*temp;

	while (lexer)
	{
		temp = lexer;
		lexer = lexer->next;
		free(temp->inf);
		free(temp);
	}
}

void    free_argv(t_parcer *cmd)
{
    int i;

    if (!cmd || !cmd->argv)
        return;
    i = 0;
    while (cmd->argv[i])
        free(cmd->argv[i++]);   // libera los strdup hechos en append_arg
    free(cmd->argv);            // libera la matriz (malloc de append_arg)
    cmd->argv = NULL;
    cmd->argc = 0;
}
void	free_parcer(t_parcer *parcer)
{
	t_parcer	*temp;

	while (parcer)
	{
		temp = parcer;
		if (parcer->cmd_args)
			free(parcer->cmd_args);
		if (parcer->arg_export)
			free(parcer->arg_export);
		if (parcer->name_infile)
			free(parcer->name_infile);
		if (parcer->name_outfile)
			free(parcer->name_outfile);
		if (parcer->builtin)
			free(parcer->builtin);
		if (parcer->argv)
			free_split(parcer->argv);
		parcer = parcer->next;
		free(temp);
	}
	free_argv(parcer);
}

void	free_minishell(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->lexer)
		free_lexer(mini->lexer);
	if (mini->parcer)
		free_parcer(mini->parcer);
	free(mini);
}

void	free_shell(t_shell *envi)
{
	if (!envi)
		return ;
	if (envi->envi)
		free_split(envi->envi);
}
