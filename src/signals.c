/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:39:53 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/01 13:09:15 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	suppress_output(void)
{
	struct termios	new_term;

	if (tcgetattr(0, &new_term) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	new_term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &new_term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	sigint_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		write(2, "Quit: 3\n", 9);
	}
	write(1, "\n", 1);
	rl_on_new_line();
}

void	signal_interactive(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_non_interactive(void)
{
	signal(SIGINT, sigquit_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	set_signals(void)
{
	suppress_output();
	if (isatty(STDIN_FILENO))
		signal_interactive();
	else
		signal_non_interactive();
}