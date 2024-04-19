/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:39:53 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/18 17:05:10 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigint_main(int signum)
{
	(void) signum;
	g_signal = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDERR_FILENO, "\n", 1);
	rl_redisplay();
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
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	(void) signum;
	g_signal = 130;
	exit(130);
}

void	signals_cmd(int signum)
{
	(void) signum;
	g_signal = 130;
	rl_replace_line("", 0);
	write(1, "\n", 2);
}

void	reset_line(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", STDERR_FILENO);
	rl_redisplay();
}
