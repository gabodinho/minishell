/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:30:04 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/16 15:08:00 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "execution.h"
#include "builtins.h"

static int	longer_str(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str1));
	else
		return (ft_strlen(str2));
}

static void	write_to_pipe(int pfd[2], t_node *node)
{
	char	*buf;

	close(pfd[0]);
	while (1)
	{
		buf = readline("heredoc> ");
		if (!buf)
		{
			write(1, "\nminishell: warning: \
here-document delimited by end-of-file\n", 60);
			break ;
		}
		if (!ft_strncmp(node -> delim, buf, longer_str(buf, node -> delim)))
			break ;
		write(pfd[1], buf, ft_strlen(buf));
		write(pfd[1], "\n", 1);
	}
	close(pfd[1]);
	free(buf);
	exit(g_signal);
}

void	run_here(t_node *node, t_data *data, int is_builtin)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	// reset_stdin();
	// reset_stdout();
	int	tty_fd = open("/dev/tty", O_RDONLY);
	dup2(tty_fd, STDIN_FILENO);
	status = 0;
	signal(SIGINT, set_signals_heredoc);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(pipe_fd) == -1)
		panic("heredoc: pipe", errno);
	pid = fork();
	if (pid < 0)
		panic("heredoc: fork", errno);
	else if (pid == 0)
		write_to_pipe(pipe_fd, node);
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		waitpid(0, &status, 0);
	}
	if (is_builtin || WEXITSTATUS(status) == SIGINT)
		return ;
	run_tree(node -> subnode, data);
}
/*
static void	write_to_pipe2(int fd, t_node *node)
{
	char	*buf;
	
	while (1)
	{
		buf = readline("heredoc> ");
		if (!buf)
		{
			write(1, "\nminishell: warning: \
here-document delimited by end-of-file\n", 60);
			break ;
		}
		if (!ft_strncmp(node -> delim, buf, longer_str(buf, node -> delim)))
			break ;
		
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	close(fd);
	fd = open("tempfile.txt", O_RDONLY, 0600);
	unlink("tempfile.txt");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	run_here(t_node *node, t_data *data, int is_builtin)
{
	int		status;

	int	fd = open("tempfile.txt", O_CREAT | O_RDWR | O_EXCL, 0600);

	status = 0;
	signal(SIGINT, set_signals_heredoc);
	signal(SIGQUIT, SIG_IGN);
	write_to_pipe2(fd, node);
	if (is_builtin || WEXITSTATUS(status) == SIGINT)
		return ;
	run_tree(node -> subnode, data);
}
*/