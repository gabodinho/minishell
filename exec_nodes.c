/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:43:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/19 16:03:04 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	run_redir(t_node *node, t_list *envir)
{
	int	new_fd;
	int	saved_stdout;

	if (!node -> file)
		panic("missing file");
	//close(node -> fd);
	new_fd = open(node->file, node->mode, 0666);
	if (new_fd < 0)
	{
		perror("open");
		panic(node->file);
	}
	printf("opened file: %s with mode %d\n", node->file, node->mode);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	run_tree(node -> subnode, envir);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

//	if (open(node -> file, node -> mode, 0666) < 0)
//		panic(node -> file);
//	run_tree(node -> subnode, envir);
}

int	is_path(char *str)
{
	if (str[0] == '/')
		return (1);
	return (0);
}

static void	run_exec(t_node *node, t_list *envir)
{
	char	*path_to_exec;
	char	**env_arr;

	env_arr = conv_env(envir);
	/*
	// check wheter node -> param[0] is already a path
	if (!is_path(node -> param[0]))				// todo
		path_to_exec = exp_rel_path(node -> param[0]);	// todo inclusive access check
	// search builtins
	else if (!is_builtin(node -> param))		// todo
		run_builtin(node -> param, envir);		// todo
	else	*/
	//	path_to_exec = find_exec(node -> param[0], search_env("PATH", envir));
	//printf("path to exec: %s\n", path_to_exec);
	path_to_exec = NULL;
	if (is_builtin(node->param[0]))
	{
		exec_builtins(node->param, envir);
		del_arr(env_arr);
		return ;
	}
	else if (is_path(node -> param[0]))
		path_to_exec = ft_strdup(node -> param[0]);
	else
	{
		path_to_exec = find_exec(node -> param[0], search_env("PATH", envir));
		printf("path to exec: %s\n", path_to_exec);
	}
	if (path_to_exec)
	{
		if (execve(path_to_exec, node -> param, env_arr) == -1)
		{
			perror("execve");
			g_exit_status = 1;
		}
		del_arr(env_arr);
		free(path_to_exec);
	}
	else if (!path_to_exec)
		g_exit_status = 127;
	else
		panic(node -> param[0]);
	del_arr(env_arr);
	free(path_to_exec);
}

static void	run_pipe(t_node *node, t_list *envir)
{
	int	p_fd[2];

	pipe(p_fd);
	if (fork() == 0)
	{
		close(1);
		dup(p_fd[1]);
		close(p_fd[0]);
		close(p_fd[1]);
		run_tree(node -> left, envir);
	}
	if (fork() == 0)
	{
		close(0);
		dup(p_fd[0]);
		close(p_fd[1]);
		close(p_fd[0]);
		run_tree(node -> right, envir);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	wait(0);
	wait(0);
}


static void	run_here(t_node *node, t_list *envir)
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
	run_tree(node -> subnode, envir);
}


void	run_tree(t_node *tree, t_list *envir)
{
	if (!tree)
		panic("no tree");
	if (tree -> ntype == N_PIPE)
		run_pipe(tree, envir);
	else if (tree -> ntype == N_REDIR)
		run_redir(tree, envir);
	else if (tree -> ntype == N_HERE)
		run_here(tree, envir);
	else
		run_exec(tree, envir);
}
