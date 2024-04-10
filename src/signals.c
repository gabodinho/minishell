/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:39:53 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/09 14:38:59 by irivero-         ###   ########.fr       */
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

void	sigint_main(int signum)
{
	g_signal = signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigint_further_tok(int signum)
{
	(void)	signum;
	g_signal = 1010;		//randomly chosen to tell the while loop in further_token function to break
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	set_signal_further_tok(void)
{
	signal(SIGINT, sigint_further_tok);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_other(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
}

void	set_signals_main(void)
{
	signal(SIGINT, sigint_main);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_other(void)
{
	signal(SIGINT, sigint_other);
	signal(SIGQUIT, sigint_other);
}

void	set_signals_heredoc(int signum)
{
	g_signal = signum;
	//rl_replace_line("", 0);
	//rl_on_new_line();
	rl_clear_history();
	exit(0);
}

void	signals_cmd(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
}

void	display_new_line(int signum)
{
	(void) signum;
	exit(0);
}
