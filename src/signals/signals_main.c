/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:22:12 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/18 17:10:41 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	set_signal_further_tok(void)
{
	signal(SIGINT, sigint_further_tok);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_main(void)
{
	signal(SIGINT, sigint_main);
	signal(SIGQUIT, SIG_IGN);
}

int	get_exit_status(int status)
{
	int	exit_status;

	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else
		exit_status = g_signal;
	return (exit_status);
}

void	set_signals_cmd(void)
{
	signal(SIGINT, signals_cmd);
	signal(SIGQUIT, sigquit_cmd);
}

void	sigquit_cmd(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	write(1, "Quit: (core dumped)\n", 20);
	g_signal = 131;
}
