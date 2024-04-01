/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:52:03 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/29 16:06:01 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

int	get_exit_status(int status)
{
	int	exit_status;

	exit_status = WEXITSTATUS(status);
	if (!WIFEXITED(status))
		perror("abnormal exit");
	return (exit_status);
}

int	is_builtin_exec(t_node *tree)
{
	if (tree -> ntype == N_PIPE)
		return (1);
	while (tree -> ntype != N_EXE)
		tree = tree -> subnode;
	if (is_builtin(tree -> param[0]))
		return (0);
	else
		return (1);
}
