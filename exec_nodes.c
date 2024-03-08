/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:43:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/08 18:45:07 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	run_redir(t_node *node)
{
	close(node -> fd);
	
	if (open(node -> file, node -> mode, 0666) < 0)
	{
		printf("opening %s failed\n", node -> file);
		exit(1);
	}
	run_tree(node -> subnode);
}

static void	run_exec(t_node *node)
{
	execve(node -> param[0], node -> param, NULL);
	printf("executing %s failed\n", node -> param[0]);
	exit(1);
}

static void	run_pipe(t_node *node)
{
	int	p_fd[2];

	pipe(p_fd);
	if (fork() == 0)
	{
		close(1);
		dup(p_fd[1]);
		close(p_fd[0]);
		close(p_fd[1]);
		run_tree(node -> left);
	}
	if (fork() == 0)
	{
		close(0);
		dup(p_fd[0]);
		close(p_fd[1]);
		close(p_fd[0]);
		run_tree(node -> right);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	wait(0);
	wait(0);
}

/*
static void	run_here(t_node *node)
{

}
*/

void	run_tree(t_node *tree)
{
	if (!tree)
		exit(1);
	if (tree -> ntype == N_PIPE)
		run_pipe(tree);
	else if (tree -> ntype == N_REDIR)
		run_redir(tree);
//	else if (tree -> ntype == N_HERE)
//		run_here(tree);
	else
		run_exec(tree);
}
