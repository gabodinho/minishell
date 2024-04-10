/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:22:12 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 15:30:24 by irivero-         ###   ########.fr       */
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
