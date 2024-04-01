/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:21:00 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/29 16:07:44 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "builtins.h"
# include "expander.h"
# include "parser.h"
# include "tokenizer.h"
# include "libft.h"

int get_exit_status(int status);
int	is_builtin_exec(t_node *tree);

#endif
