/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:43:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/16 14:09:28 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "execution.h"
#include "builtins.h"

int	run_tree(t_node *tree, t_data *data)
{
	int	exit_val;

	exit_val = 0;
	if (tree -> ntype == N_PIPE)
		exit_val = run_pipe(tree, data);
	else if (tree -> ntype == N_REDIR)
		run_redir(tree, data, 0);
	else if (tree -> ntype == N_HERE)
		run_here(tree, data, 0);
	else if (is_builtin(tree -> param[0]))
		exit_val = exec_builtins(tree -> param, data);
	else
		run_exec(tree, data);
	exit(exit_val);
}

// make this function return the return values of the builtins
int	run_builtin_tree(t_data *data)
{
	int		return_val;
	t_node	*tree;

	tree = data -> tree;
	return_val = 1;
	while (tree)
	{
		if (tree -> ntype == N_REDIR)
			run_redir(tree, data, 1);
		else if (tree -> ntype == N_HERE)
			run_here(tree, data, 1);
		else
		{
			return_val = exec_builtins(tree->param, data);
			reset_stdin();
			reset_stdout();
		}
		if (g_signal == 2020)
			return (1);
		tree = tree -> subnode;
	}
	return (return_val);
}
