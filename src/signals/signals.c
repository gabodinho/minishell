/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:39:53 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 15:29:51 by irivero-         ###   ########.fr       */
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
	g_signal = signum;
	rl_clear_history();
	exit(0);
}

void	signals_cmd(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
}

void	display_new_line(int signum)
{
	(void)signum;
	exit(0);
}
