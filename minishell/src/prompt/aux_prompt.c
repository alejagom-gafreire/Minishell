/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:25:20 by alejandro         #+#    #+#             */
/*   Updated: 2026/05/26 20:55:13 by gafreire         ###   ########.fr       */
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
	write(1, "\n          Welcome to MiniShell  \n", 35);
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
		printf("\r\033[2K%sStarting...", frames[i % n]);
		fflush(stdout);
		usleep(50000);
		i++;
	}
	printf(BRIGHT_BLUE BOLD "\r\033[2K          🎇✔ MiniShell ready!🎇  \n");
	fflush(stdout);
}

char	*create_prompt(void)
{
	const char	*user;
	char		*prompt;

	user = getenv("USER");
	if (!user || !*user)
		user = "user";
	prompt = ft_strdup("🤖 ");
	if (!prompt)
		return (NULL);
	if (append_part(&prompt, BRIGHT_GREEN BOLD))
		return (NULL);
	if (append_part(&prompt, user))
		return (NULL);
	if (append_part(&prompt, RESET))
		return (NULL);
	if (append_part(&prompt, " ➤ "))
		return (NULL);
	if (append_minish(&prompt))
		return (NULL);
	return (prompt);
}
