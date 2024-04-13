/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:32:01 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/11 02:32:06 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "execution.h"
#include "builtins.h"

static void	manage_pipe(int pfd[2], int fd, t_node *tree, t_data *data)
{
	if (fd == STDOUT_FILENO)
		dup2(pfd[1], fd);
	else
		dup2(pfd[0], fd);
	close(pfd[0]);
	close(pfd[1]);
	run_tree(tree, data);
}

int	run_pipe(t_node *node, t_data *data)
{
	int	p_fd[2];
	int	pid1;
	int	pid2;
	int	status;

	pipe(p_fd);
	pid1 = fork();
	if (pid1 < 0)
		panic("pipe: fork", errno);
	else if (pid1 == 0)
		manage_pipe(p_fd, STDOUT_FILENO, node -> left, data);
	else
	{
//		wait(0);
		pid2 = fork();
		if (pid2 < 0)
			panic("pipe: fork", errno);
		else if (pid2 == 0)
			manage_pipe(p_fd, STDIN_FILENO, node -> right, data);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	wait(0);
	waitpid(0, &status, 0);
	return (WEXITSTATUS(status));
}
