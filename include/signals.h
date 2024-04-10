/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:40:14 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 15:29:43 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "tokenizer.h"
# include "structs.h"


extern int	g_signal;

void	suppress_output(void);
void	sigint_main(int signum);
void	set_signals_main(void);
void	set_signals_heredoc(int signum);
void	signals_cmd(int signum);
void	display_new_line(int signum);
void	sigint_further_tok(int signum);
void	set_signal_further_tok(void);


#endif
