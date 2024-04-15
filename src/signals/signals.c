/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:39:53 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/11 13:30:33 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigint_main(int signum)
{
	g_signal = signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigint_further_tok(int signum)
{
	(void)signum;
	g_signal = 1010;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	set_signals_heredoc(int signum)
{
	rl_clear_history();
	rl_on_new_line();
	// write(1, "\n", 1);
	exit(signum);
}

void	signals_cmd(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	// rl_on_new_line();
	write(1, "\n", 2);
	// rl_redisplay();
	//exit(0);
}


void	reset_line(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", STDERR_FILENO);
	rl_redisplay();
}

void	display_new_line(int signum)
{
	(void)signum;


	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "QUIT\n", 2);
	// rl_on_new_line();
	// rl_redisplay();
	//exit(0);
}
/*
void	our_sigint(int	signum)
{
	signal(signum, SIG_IGN);
	kill(g_signal, SIGUSR1);
}

void	our_sigusr1(int signum)
{
	(void)	signum;
	write(1, "\n", 1);
}
*/