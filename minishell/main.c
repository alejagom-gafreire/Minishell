/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-08 14:09:27 by gafreire          #+#    #+#             */
/*   Updated: 2025-07-08 14:09:27 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define GREEN "\033[1;32m"
#define BLUE  "\033[1;34m"
#define RESET "\033[0m"

char *generar_prompt(void)
{
    char *user = getenv("USER");
    if (!user)
        user = "user"; // valor por defecto

    char *cwd = getcwd(NULL, 0); // getcwd devuelve malloc
    if (!cwd)
        cwd = strdup("unknown"); // por si falla getcwd

    const char *emoji = "🧠 ";
    const char *middle = " in ";
    const char *end = " ➤ ";

    // calcular tamaño total
    size_t size = strlen(emoji) + strlen(GREEN) + strlen(user) + strlen(RESET)
                + strlen(middle) + strlen(BLUE) + strlen(cwd) + strlen(RESET)
                + strlen(end) + 1;

    char *prompt = malloc(size);
    if (!prompt)
    {
        free(cwd);
        return NULL;
    }

    // construir el prompt con sprintf
    sprintf(prompt, "%s%s%s%s%s%s%s%s%s",
            emoji,
            GREEN, user, RESET,
            middle,
            BLUE, cwd, RESET,
            end);

    free(cwd); // liberar getcwd

    return prompt;
}

int check_token(int argc,char *argv[])
{
    char *line;
    char *prompt;

    (void) argc;
    (void) argv;

     while (1)
    {
        prompt = generar_prompt();
        if (!prompt)
            break;

        line = readline(prompt);
        free(prompt);

        if (!line) // Ctrl+D
        {
            printf("exit\n");
            break;
        }

        if (*line)
            add_history(line); // guarda en historial si no está vacío

        // acá podrías imprimir, parsear, ejecutar...
        free(line);
    }
    return (0);
}

int main (int argc, char *argv[])
{
    if (argc > 1)
    {
        check_token(argc,argv);
    }
    else
    {

        printf("Esta mal");
    }
    return (0);
}