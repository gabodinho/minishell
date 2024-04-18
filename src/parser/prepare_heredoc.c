/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:57:31 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/18 17:07:20 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "signals.h"

static int	longer_str(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str1));
	else
		return (ft_strlen(str2));
}

/*
// version without fork()
static void	write_to_pipe(int pfd[2], char *delim)
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
		if (!ft_strncmp(delim, buf, longer_str(buf, delim)))
			break ;
		write(pfd[1], buf, ft_strlen(buf));
		write(pfd[1], "\n", 1);
		free(buf);
	}
	close(pfd[1]);
}
*/
static void	write_to_pipe(int pfd[2], char *delim)
{
	char	*buf;

	close(pfd[0]);
	while (1)
	{
		buf = readline("> ");
		if (!buf)
		{
			write(1, "minishell: warning: \
here-document delimited by end-of-file\n", 60);
			break ;
		}
		if (!ft_strncmp(delim, buf, longer_str(buf, delim)))
			break ;
		write(pfd[1], buf, ft_strlen(buf));
		write(pfd[1], "\n", 1);
		free(buf);
	}
	close(pfd[1]);
	free(buf);
	exit(g_signal);
}

void	prepare_heredoc(t_node *node)
{
	int	pid;
	int	status;

	signal(SIGINT, set_signals_heredoc);
	signal(SIGQUIT, SIG_IGN);
	status = 0;
	if (pipe(node -> pfd) < 0)
		return (ft_putendl_fd("heredoc: pipe", 2));
	pid = fork();
	if (pid < 0)
		return (ft_putendl_fd("heredoc: fork", 2));
	else if (pid == 0)
		write_to_pipe(node -> pfd, node -> delim);
	else
	{
		signal(SIGINT, SIG_IGN);
		close(node -> pfd[1]);
		waitpid(0, &status, 0);
		g_signal = WEXITSTATUS(status);
	}
}

void	close_pfds(t_node *node)
{
	close(node -> pfd[0]);
}

void	traverse_tree(t_node *tree, void (*handler)(t_node *))
{
	if (!tree)
		return ;
	if (tree -> ntype == N_HERE)
		handler(tree);
	if (tree -> ntype == N_PIPE)
	{
		traverse_tree(tree -> left, handler);
		traverse_tree(tree -> right, handler);
	}
	else if (tree)
		traverse_tree(tree -> subnode, handler);
}
