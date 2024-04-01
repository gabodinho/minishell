/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:43:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/01 19:22:24 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	run_redir(t_node *node, t_list **envir)
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
	if (str[0] == '/' || str[0] == '.')
		return (1);
	return (0);
}

void	reset_stdin(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_RDONLY);
	dup2(tty_fd, STDIN_FILENO);
	close(tty_fd);
}

// !!!ACHTUNG builtins sollten vor der Ausführung des trees ausgeführt werden um nichtin jedem exec node eine kopie des envirs zu haben -> oder Alternativen?
static void	run_exec(t_node *node, t_list **envir)
{
	char	*path_to_exec;
	char	**env_arr;

	env_arr = conv_env(*envir);
	path_to_exec = NULL;
	// // check wheter node -> param[0] is already a path
	// if (!access(node -> param[0], F_OK))
	// 	path_to_exec = node -> param[0];
	// else if (*node -> param[0] == '~')
	// 	path_to_exec = exp_home(node -> param[0], envir);
	// // search builtins
	// else if (!is_builtin(node -> param))		// todo
	// 	run_builtin(node -> param, envir);		// todo
	// else	*/
	// //	path_to_exec = find_exec(node -> param[0], search_env("PATH", envir));
	// //printf("path to exec: %s\n", path_to_exec);
	// path_to_exec = NULL;
	if (is_path(node -> param[0]))
		path_to_exec = ft_strdup(node -> param[0]);
	else
	{
		path_to_exec = find_exec(node -> param[0], search_env("PATH", *envir));
		printf("path to exec: %s\n", path_to_exec);
	}
	if (path_to_exec)
	{
		if (execve(path_to_exec, node -> param, env_arr) == -1)
		{
			panic(node -> param[0]);
			g_exit_status = 1;
		}
		panic(node -> param[0]);
		del_arr(env_arr);
		free(path_to_exec);
	}
	else if (!path_to_exec)
		g_exit_status = 127;
	else
		panic(node -> param[0]);

	del_arr(env_arr);
	free(path_to_exec);
	panic(node -> param[0]);
}

static void	run_pipe(t_node *node, t_list **envir)
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

void	write_to_pipe(int pfd[2], t_node *node)
{
	char	*buf;

	close(pfd[0]);
	while (1)
	{
		buf = readline("heredoc> ");
		if (!buf)
			panic("heredoc: readline");
		if (!ft_strncmp(node -> delim, buf, ft_strlen(buf)))
			break ;
		write(pfd[1], buf, ft_strlen(buf));
		write(pfd[1], "\n", 1);
	}
	close(pfd[1]);
	free(buf);
}


static void	run_here(t_node *node, t_list **envir)
{
	int		pipe_fd[2];
	pid_t	pid;

	reset_stdin();
	if (pipe(pipe_fd) == -1)
		panic("heredoc: pipe");
	pid = fork();
	if (pid < 0)
		panic("heredoc: fork");
	else if (pid == 0)
	{
		write_to_pipe(pipe_fd, node);
		exit(0);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		wait(0);
	}
	run_tree(node -> subnode, envir);
}

void	run_tree(t_node *tree, t_list **envir)
{
	pid_t	pid;
	
	if (!tree)
		panic("no tree");
	if (is_builtin(tree->param[0]))
	{
		exec_builtins(tree->param, envir);
		return ;
	}
	pid = fork();
	if (pid < 0)
		panic("fork");
	else if (pid == 0)
	{
		if (tree->ntype == N_PIPE)
			run_pipe(tree, envir);
		else if (tree->ntype == N_REDIR)
			run_redir(tree, envir);
		else if (tree->ntype == N_HERE)
			run_here(tree, envir);
		else
			run_exec(tree, envir);
	}
	else
		waitpid(pid, NULL, 0);
}

/*
void	run_tree(t_node *tree, t_list **envir)
{
	if (!tree)
		panic("no tree");
	if (tree -> ntype == N_PIPE)
		run_pipe(tree, envir);
	else if (tree -> ntype == N_REDIR)
		run_redir(tree, envir);
	else if (tree -> ntype == N_HERE)
		run_here(tree, envir);
	else if (is_builtin(tree -> param[0]))
		exec_builtins(tree -> param, envir);
	else
		run_exec(tree, envir);
}
*/