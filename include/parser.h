/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:25:38 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/03 20:01:29 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_printf.h"
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> //getcwd, chdir, fork, execve, wait, write, read, pipe, dup, dup2, close, isatty, ttyname, ttyslot, unlink
# include <string.h> // strerror, perror
# include <sys/wait.h> // waitpid, wait3, wait4
# include <sys/stat.h> // stat, lstat, fstat, access, open, read, close
# include <fcntl.h> // open, read, close, access
# include <errno.h>
//# include <readline/readline.h> // readline
//# include <readline/history.h> // history
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h> // opendir, closedir, readdir
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcgetattr, tcsetattr
# include <ncurses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# define T_NULL 0
# define WORD 1
# define PIPE 2
# define REDIR 3
//# define DLESS 3
//# define DGREAT 4
//# define LESS 5
//# define GREAT 6
//# define HEREDOC 4
# define DOUBLE_QUOTES 4
# define SINGLE_QUOTES 5

typedef enum e_ntype
{
	N_REDIR,
	N_HERE,
	N_PIPE,
	N_EXE
}	t_ntype;

typedef struct s_node
{
	t_ntype	ntype;
	struct s_node	*right;	//pipenode
	struct s_node   *left;
	struct s_node   *subnode;//allnodes
	char	*param[20];		//exenode
	char	*file;			//redirnode
	int		mode;
	int		fd;
	char	*delim;			//herenode
}	t_node;
/*
typedef struct s_pipecmd
{
	t_ntype	ntype;
	void	*left;
	void	*right;
}	t_pipecmd;

typedef struct s_execmd
{
	t_ntype ntype;
	char	*param[20];
	void	*subnode;
}	t_node;

typedef struct s_redircmd
{
	t_ntype ntype;
	char	*file;
	int		mode;
	int		fd;
	void	*subnode;
}	t_redircmd;

typedef struct s_herecmd
{
	t_ntype ntype;
	char	*delim;
	void	*subnode;
}	t_node;
*/

typedef struct s_token
{
	char	*str;
	int		type;
	struct s_token	*next;
}	t_token;

t_node	*heredoc_cmd(t_token *token);
t_node	*redir_cmd(t_token *token);
t_node	*pipe_cmd(t_token **left_list, t_token **right_list);
t_node    *parse_redir(t_node *cmd, t_token **toklist);
t_node	*init_node(void);
void	add_attribute(t_node *node, char *str);
t_node	*parse_exe(t_token **toklist);
t_node	*parse_pipe(t_token **toklist);

#endif
