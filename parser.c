/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:51:44 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/02/22 17:03:45 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> //getcwd, chdir, fork, execve, wait, write, read, pipe, dup, dup2, close, isatty, ttyname, ttyslot, unlink
# include <string.h> // strerror, perror
# include <sys/wait.h> // waitpid, wait3, wait4
# include <sys/stat.h> // stat, lstat, fstat, access, open, read, close
# include <fcntl.h> // open, read, close, access
# include <errno.h>
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h> // opendir, closedir, readdir
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcgetattr, tcsetattr
# include <ncurses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

typedef struct s_pipecmd
{
	void	*left;
	void	*right;
}	t_pipecmd;

typedef struct s_execmd
{
	char	**param;
}	t_execmd;

typedef struct s_heredoccmd
{
	char	*delim;
	char	*subnode;
}	t_heredoccmd;

typedef struct s_redircmd
{
	char	*file;
	char	*mode;
	int		fd;
	void	*subnode;
}	t_redircmd;

typedef struct s_token
{
	char	*token;
	char	*category;
}	t_token;

void	*parse_redir(void *cmd, t_token **toklist);
t_execmd	*init_execmd(void);
void	add_attribute(t_execmd *cmd, char *str);
t_pipecmd	*pipe_cmd(t_token **toklist, void *cmd);

void	*parse_exe(t_token **toklist)
{
	t_execmd	*execmd;
	void		*cmd;
	t_token		*token;

	execmd = init_execmd();		// wip
	token = *toklist;
	cmd = parse_redir(execmd, &token);			// wip
	while (token)
	{
		if (token -> type == PIPE)
			break ;
		else if (token -> type == WORD)
			add_attribute(execmd, token -> str);		// wip
		token = token -> next;
		cmd = parse_redir(cmd, &token);
	}
	return (cmd);
}
			
void	*parse_pipe(t_token **toklist)
{
	void	*cmd;
	t_token	*token;

	token = *toklist;
	while (token && token -> type != PIPE)
		token = token -> next;
	if (token && token -> type == PIPE)
		cmd = (*t_pipecmd) pipe_cmd(toklist, parse_pipe(&(token -> next)));	// wip
	else if (*toklist)
		cmd = (*t_execmd) parse_exe(start);
	else
		return (NULL);
	return (cmd);
}
