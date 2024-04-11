/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:30:04 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/11 14:18:37 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "execution.h"
#include "builtins.h"

static int	longer_str(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str1) - 1);
	else
		return (ft_strlen(str2));
}

static void	write_to_pipe(int pfd[2], t_node *node)
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
	exit(g_signal);
}

void	run_here(t_node *node, t_data *data, int is_builtin)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	status = 0;
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
		waitpid(0, &status, 0);
	}
	if (is_builtin || WEXITSTATUS(status) == SIGINT)
		return ;
	run_tree(node -> subnode, data);
}
