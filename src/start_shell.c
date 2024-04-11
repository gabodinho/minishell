/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:46:54 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/11 21:53:40 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	print_color_text(char *text, char *color)
{
	char	*color_code;

	color_code = "";
	if (ft_strcmp(color, "red") == 0)
		color_code = "\033[31m";
	else if (ft_strcmp(color, "green") == 0)
		color_code = "\033[32m";
	else if (ft_strcmp(color, "yellow") == 0)
		color_code = "\033[33m";
	write(1, color_code, ft_strlen(color_code));
	write(1, text, ft_strlen(text));
	write(1, "\033[0m", 4);
}

void	print_line(const char *line)
{
	write(1, line, ft_strlen(line));
}

void	print_tab(const char *line, int num_tabs)
{
	int	i;

	i = 0;
	while (i < num_tabs)
	{
		write(1, "\t", 1);
		i++;
	}
	write(1, line, ft_strlen(line));
}

void	print_text(void)
{
	print_tab(GREEN" _______ _________ _       _________\n"RESET, 1);
	print_tab(GREEN"(       )\\__   __/( (    /|\\__   __/\n"RESET, 1);
	print_tab(GREEN"| () () |   ) (   |  \\  ( |   ) (   \n"RESET, 1);
	print_tab(GREEN"| || || |   | |   |   \\ | |   | |   \n"RESET, 1);
	print_tab(GREEN"| |(_)| |   | |   | (\\ \\) |   | |   \n"RESET, 1);
	print_tab(GREEN"| |   | |   | |   | | \\   |   | |   \n"RESET, 1);
	print_tab(GREEN"| )   ( |___) (___| )  \\  |___) (___\n"RESET, 1);
	print_tab(GREEN"|/     \\|\\_______/|/    )_)\\_______/\n"RESET, 1);
}

void	print_another_text(void)
{
	print_tab(GREEN" _______           _______  _        _       \n"RESET, 3);
	print_tab(GREEN"(  ____ \\|\\     /|(  ____ \\( \\      ( \\      \n"RESET, 3);
	print_tab(GREEN"| (    \\/| )   ( || (    \\/| (      | (      \n"RESET, 3);
	print_tab(GREEN"| (_____ | (___) || (__    | |      | |      \n"RESET, 3);
	print_tab(GREEN"(_____  )|  ___  ||  __)   | |      | |      \n"RESET, 3);
	print_tab(GREEN"      ) || (   ) || (      | |      | |      \n"RESET, 3);
	print_tab(GREEN"/\\____) || )   ( || (____/\\| (____/\\| (____/\\\n"RESET, 3);
	print_tab(GREEN"\\_______)|/     \\|(_______/(_______/(_______/\n"RESET, 3);
}

void	welcome_message(void)
{
	char	*welcome_text;

	print_text();
	print_another_text();
	welcome_text = "\n\t\t\t\t\t\t\t\t\tBy ggiertzu & irivero-\n";
	print_color_text(welcome_text, "red");
	printf("\n");
}
