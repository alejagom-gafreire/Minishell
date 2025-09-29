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

void	print_slow(const char *str, unsigned int delay)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
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
	write(1, "\n          Bienvenido a MiniShell  \n", 36);
	printf("\n");
	printf("            🚀 🧠 🧠 🧠 🧠 🚀\n");
	printf(BOLD "           Gabriel Simón Freire\n" RESET);
	printf(BOLD "             Alejandro Gómez\n" RESET);
	printf("\n");
}

void	spinner_loading(void)
{
	const char	*frames[] = {"         🚀          ",
		"          🎇🚀         ", "          🌫️🎇🚀         ",
		"          🌫️🌫️🎇🚀        ",
		"          🌫️🌫️🌫️🎇🚀       ",
		"          🌫️🌫️🌫️🌫️🎇🚀      ",
		"          🌫️🌫️🌫️🌫️🌫️🎇🚀     ",
		"          🌫️🌫️🌫️🌫️🌫️🌫️🎇🚀    ",
		"          🌫️🌫️🌫️🌫️🌫️🌫️🌫️🎇🚀   ",
		"          🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🎇🚀  ",
		"          🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🎇🚀 ",
		"          🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🌫️🎇🚀"};
	int			n;
	int			i;

	n = sizeof(frames) / sizeof(frames[0]);
	i = 0;
	while (i < 30)
	{
		printf("\r%sStarting...", frames[i % n]);
		fflush(stdout);
		usleep(50000);
		i++;
	}
	printf(BRIGHT_BLUE BOLD "\r          🎇✔ MiniShell lista!🎇  \n");
}

char	*create_prompt(void)
{
	char	*user;
	size_t	size;
	char	*prompt;

	user = getenv("USER");
	if (!user)
		user = "user";
	size = ft_strlen("🧠 ") + ft_strlen(CYAN BOLD) + ft_strlen(user)
		+ ft_strlen(RESET) + ft_strlen(" in ") + ft_strlen(BLUE)
		+ ft_strlen("Minishell") + ft_strlen(RESET)
		+ ft_strlen(" ➤ ") + 1;
	prompt = malloc(size);
	if (!prompt)
		return (NULL);
	sprintf(prompt, "🤖 %s%s%s ➤ %sMinishell%s: ", BRIGHT_GREEN BOLD, user,
		RESET, BRIGHT_GREEN BOLD, RESET);
	return (prompt);
}
