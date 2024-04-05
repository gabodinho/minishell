/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:52:03 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/05 13:26:37 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

int	get_exit_status(int status)
{
	int	exit_status;

	exit_status = WEXITSTATUS(status);
	if (!WIFEXITED(status))
		exit_status = 1;
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
