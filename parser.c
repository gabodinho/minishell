/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:51:44 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/02/24 18:57:56 by ggiertzu         ###   ########.fr       */
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

typedef enum e_ntype
{
	REDIR,
	HERDOC,
	PIPE,
	EXEC
}	t_ntype;

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
}	t_execmd;

typedef struct s_redircmd
{
	t_ntype ntype;
	char	*file;
	char	*mode;
	int		fd;
	void	*subnode;
}	t_redircmd;

typedef struct s_herecmd
{
	t_ntype ntype;
	char	*delim;
	void	*subnode;
}	t_herecmd;

typedef struct s_token
{
	char	*str;
	char	*type;
	t_token	*next;
}	t_token;

t_pipecmd	*pipe_cmd(t_token **left_list, t_token **right_list);
{
	t_pipecmd	*node;

	node = malloc(sizeof(t_pipecmd));
	node -> left = parse_exe(left_list);
	node -> right = parse_pipe(right_list);
}

void    *parse_redir(void *cmd, t_token **toklist)
{
	void	*redircmd;

	if ((*token) -> type = REDIR)
		redircmd = redir_cmd(toklist);		// wip (increment toklist)
	else if ((*token) -> type = HEREDOC)
		redircmd = heredoc_cmd(toklist);		// wip (inkrement toklist)
	else
		return (cmd);
	redircmd -> subnode = cmd;
	return (redircmd);
}

t_execmd	*init_execmd(void)
{
	t_execmd	*node;
	int			i;

	node = malloc(sizeof(t_execmd));
	i = 0;
	while (i < 20)
		(node -> param)[i] = NULL;
	return (node);
}

void	add_attribute(t_execmd node, char *str)
{
	int	i;

	i = 0;
	while (i < 20 && (node -> param)[i])
		i++;
	if (i == 20)
		throw_error("param limit in exec node");		// wip
	else 
		(node -> param)[i] = str;
}

void	*parse_exe(t_token **toklist)
{
	t_execmd	*execmd;
	void		*cmd;
	t_token		*token;

	if (!*toklist)
		return (NULL);
	execmd = init_execmd();
	token = *toklist;
	cmd = parse_redir(execmd, &token);
	while (token)
	{
		if (token -> type == PIPE)
			break ;
		else if (token -> type == WORD)
			add_attribute(execmd, token -> str);
		token = token -> next;
		cmd = parse_redir(cmd, &token);
	}
	add_attribute(execmd, NULL);
	return (cmd);
}

// returns pipe node with two children or exec node with one child
void	*parse_pipe(t_token **toklist)
{
	void	*cmd;
	t_token	*token;

	token = *toklist;
	while (token && token -> type != PIPE)
		token = token -> next;
	if (token && token -> type == PIPE)		// create pipe node
		cmd = (*t_pipecmd) pipe_cmd(toklist, &(token -> next));	// wip
	else if (*toklist)		// create (left) exec node
		cmd = (*t_execmd) parse_exe(toklist);
	else		// empty list
		return (NULL);
	return (cmd);
}
