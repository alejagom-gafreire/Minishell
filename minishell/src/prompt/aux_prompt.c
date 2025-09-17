/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:25:20 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/17 19:25:22 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_slow(const char *str, useconds_t delay)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		fflush(stdout);
		usleep(delay);
		i++;
	}
}

void	print_banner(void)
{
	const char	*banner;

	printf("\n");
	printf("\n");
	banner = "   ███▄ ▄████  ██▓ ███▄   ██ ▄███ ███████ ██   ██░██▓     ██▓\n"
		"   ▓██▒▀█▀ ██▒▓██▒ ██ ▀█  ██  ██▒ ██    ▒ ██▓  ██░██▒    ▓██▒ \n"
		"   ▓██    ▓██░▒██▒▓██  ▀█ ██▒▓██░  ███▄   ██▒████░██░    ▒██░ \n"
		"   ▒██    ▒██ ░██░▓██▒  ▐▌██▒▓██▓  ▒  ███▒██▒  ██▓██░    ▒██░ \n"
		"   ▒██▒   ░██▒░██░▒██░   ███░▒██▒ ███████▒██░  ██ ██████▒░██████▒\n"
		"   ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒   ▒ ░░  ▒░▓  ░ ░ ▒░▓  ▓░ ▒░▓  ░\n";
	print_slow(banner, 700);
	write(1, "\n🚀 Bienvenido a MiniShell v1.0 🚀\n\n", 36);
}

void	spinner_loading(void)
{
	const char	*frames[] = {"                🚀          ",
		"                 🎇🚀         ", "                 🌫️🎇🚀         ",
		"                 🌫️🌫️🎇🚀        ",
		"                 🌫️🌫️🌫️🎇🚀       ",
		"                 🌫️🌫️🌫️🌫️🎇🚀      ",
		"                 🌫️🌫️🌫️🌫️🌫️🎇🚀     ",
		"                 🌫️🌫️🌫️🌫️🌫️🌫️🎇🚀    ",
		"                 🌫️🌫️🌫️🌫️🌫️🌫️🌫️🎇🚀   ",
		"                 🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🎇🚀  ",
		"                 🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🎇🚀 ",
		"                 🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🎇🚀"};
	int			n;
	int			i;

	n = sizeof(frames) / sizeof(frames[0]);
	i = 0;
	while (i < 30)
	{
		printf("\r%sStarting...", frames[i % n]);
		fflush(stdout);
		usleep(120000);
		i++;
	}
	printf(BRIGHT_BLUE BOLD "\r                  🎇✔ MiniShell lista!🎇  \n\n");
}

int	show_menu(void)
{
	int	option;

	option = 0;
	printf(CYAN BOLD "    🧠 MiniShell Launcher\n" RESET);
	printf("--------------------------------\n");
	printf(CYAN BOLD "  📚  1. Iniciar Shell      🔥🚀\n");
	printf(CYAN BOLD "  📚  2. Créditos           🧑‍💻\n");
	printf(CYAN BOLD "  📚  3. Salir              👋⚙️\n" RESET);
	printf("--------------------------------\n");
	printf(BRIGHT_BLUE BOLD "     Seleccione opción ➤ ");
	scanf("%d", &option);
	getchar();
	return (option);
}

void	print_names(int options)
{
	if (options == 2)
	{
		printf("\n");
		printf("            🚀 🧠 🧠 🧠 🧠 🚀\n");
		printf(BRIGHT_RED "                create by\n\n" RESET);
		printf(BOLD "           Gabriel Simón Freire\n" RESET);
		printf(BOLD "             Alejandro Gómez\n" RESET);
		printf("\n");
		exit(1);
	}
	else
	{
		printf("👋 Saliendo...\n");
		exit(1);
	}
}

char	*create_prompt(void)
{
	char	*user;
	size_t	size;
	char	*prompt;

	user = getenv("USER");
	if (!user)
		user = "user";
	size = strlen("🧠 ") + strlen(CYAN BOLD) + strlen(user) + strlen(RESET)
		+ strlen(" in ") + strlen(BLUE) + strlen("Minishell") + strlen(RESET)
		+ strlen(" ➤ ") + 1;
	prompt = malloc(size);
	if (!prompt)
		return (NULL);
	sprintf(prompt, "🤖 %s%s%s ➤ %sMinishell%s: ", BRIGHT_GREEN BOLD, user,
		RESET, BRIGHT_GREEN BOLD, RESET);
	return (prompt);
}
