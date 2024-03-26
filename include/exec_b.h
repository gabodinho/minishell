/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_b.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:21:00 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/18 15:10:23 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_B_H
# define EXEC_B_H

# include "builtins.h"
# include "expander.h"
# include "parser.h"
# include "tokenizer.h"
# include "libft.h"

bool	is_builtin(char *str);
int		exec_builtins(char **av, t_list **env);

#endif
