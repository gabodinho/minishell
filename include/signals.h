/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:40:14 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/01 13:09:25 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "tokenizer.h"
# include "structs.h"


void	suppress_output(void);
void	sigint_handler(int signum);
void	sigquit_handler(int signum);
void	signal_interactive(void);
void	signal_non_interactive(void);
void	set_signals(void);

#endif
