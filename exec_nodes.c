/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:43:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/14 11:26:52 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	run_redir(t_node *node)
{
	if (!node -> file)
		panic("missing file");
	close(node -> fd);
	if (open(node -> file, node -> mode, 0666) < 0)
		panic(node -> file);
	run_tree(node -> subnode);
}

static void	run_exec(t_node *node)
{
	char	*path_to_exec;

	path_to_exec = expand_path(node -> param[0], search_env("PATH", envir));
	execve(node -> param[0], node -> param, conv_env(envir));
	panic(node -> param[0]);
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


static void	run_here(t_node *node)
{
	char	*buff;
	int		tmp_fd;
	int		prompt_fd;

	buff = NULL;
	tmp_fd = open("tmp_file", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	prompt_fd = open("/dev/tty", O_WRONLY);
	while (1)
	{
		write(prompt_fd, "heredoc>", 8);
		buff = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(node -> delim, buff, ft_strlen(node -> delim)))
			break ;
		write(tmp_fd, buff, ft_strlen(buff));
		free(buff);
	}
	close(tmp_fd);
	close(prompt_fd);
	tmp_fd = open("tmp_file", O_RDONLY);
	unlink("tmp_file");
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	run_tree(node -> subnode);
}


void	run_tree(t_node *tree)
{
	if (!tree)
		panic("no tree");
	if (tree -> ntype == N_PIPE)
		run_pipe(tree);
	else if (tree -> ntype == N_REDIR)
		run_redir(tree);
	else if (tree -> ntype == N_HERE)
		run_here(tree);
	else
		run_exec(tree);
}
