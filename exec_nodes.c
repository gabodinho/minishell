/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:43:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/09 21:32:03 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec_b.h"
#include "builtins.h"

void	set_signals_other(void);
void	set_signals_heredoc(int signum);
void	display_new_line(int signum);

int	g_signal;


static void	run_redir(t_node *node, t_data *data, int is_builtin)
{
	int	new_fd;

	if (node -> fd == STDIN_FILENO)
		reset_stdin();
	else if (node -> fd == STDOUT_FILENO)
		reset_stdout();
	new_fd = open(node->file, node->mode, 0666);
	if (new_fd < 0 && !is_builtin)
		panic(node->file);
	else if (new_fd < 0 && is_builtin)
	{
		g_signal = 2020;	// abort builtin execution
		printf("%s: No such file or directory\n", node -> file);
			return ;
	}
	dup2(new_fd, node -> fd);
	close(new_fd);
	if (!is_builtin)
		run_tree(node -> subnode, data);
	else
		return ;
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

void	reset_stdout(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_WRONLY);
	dup2(tty_fd, STDOUT_FILENO);
	close(tty_fd);
}

static void	run_exec(t_node *node, t_data *data)
{
	char	*path_to_exec;
	char	*env_str;
	char	**env_arr;

	env_arr = conv_env(*(data -> envir));
	path_to_exec = NULL;
	if (!node -> param[0])
		return ;
	if (is_builtin(node -> param[0]))
		return (exec_builtins(node -> param, data), (void) 0);
	if (is_path(node -> param[0]))
		path_to_exec = ft_strdup(node -> param[0]);
	else
	{
		env_str = search_env("PATH", *(data -> envir));
		path_to_exec = find_exec(node -> param[0], env_str);
	}
	if (path_to_exec)
		execve(path_to_exec, node -> param, env_arr);
	del_arr(env_arr);
	free(path_to_exec);
	panic(node -> param[0]);
}

void	manage_pipe(int pfd[2], int fd, t_node *tree, t_data *data)
{
	if (fd == STDOUT_FILENO)
		dup2(pfd[1], fd);
	else
		dup2(pfd[0], fd);
	close(pfd[0]);
	close(pfd[1]);
	run_tree(tree, data);
}

static void	run_pipe(t_node *node, t_data *data)
{
	int	p_fd[2];
	int	pid1;
	int	pid2;

	pipe(p_fd);
	pid1 = fork();
	if (pid1 < 0)
		panic("pipe: fork");
	else if (pid1 == 0)
		manage_pipe(p_fd, STDOUT_FILENO, node -> left, data);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			panic("pipe: fork");
		else if (pid2 == 0)
			manage_pipe(p_fd, STDIN_FILENO, node -> right, data);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	wait(0);
	wait(0);
}

int	longer_str(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return(ft_strlen(str1) - 1);
	else
		return(ft_strlen(str2));
}

void	write_to_pipe(int pfd[2], t_node *node)
{
	char	*buf;
	int		tty_fd;

	close(pfd[0]);
	tty_fd = open("/dev/tty", O_WRONLY);
	signal(SIGINT, set_signals_heredoc);
	signal(SIGQUIT, display_new_line);
	while (g_signal != SIGINT)
	{
		write(tty_fd, "heredoc> ", 9);
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
		{
			write(tty_fd, "\nminishell: warning: \
here-document delimited by end-of-file\n", 60);
			break ;
		}
		if (!ft_strncmp(node -> delim, buf, longer_str(buf, node -> delim)))
			break ;
		write(pfd[1], buf, ft_strlen(buf));
	}
	close(pfd[1]);
	close(tty_fd);
	free(buf);
	exit(0);
}


static void	run_here(t_node *node, t_data *data, int is_builtin)
{
	int		pipe_fd[2];
	pid_t	pid;

//	reset_stdin();
//	set_signals_other();
	if (pipe(pipe_fd) == -1)
		panic("heredoc: pipe");
	pid = fork();
	if (pid < 0)
		panic("heredoc: fork");
	else if (pid == 0)
		write_to_pipe(pipe_fd, node);
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		wait(0);
	}
	if (!is_builtin)
		run_tree(node -> subnode, data);
}

void	run_tree(t_node *tree, t_data *data)
{
	int	exit_val;

	exit_val = 0;
	if (tree -> ntype == N_PIPE)
		run_pipe(tree, data);
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
	int	return_val;
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
