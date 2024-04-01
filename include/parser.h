/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:25:38 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/18 14:10:39 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_printf.h"
# include "tokenizer.h"
# include "exec_b.h"
# include "builtins.h"
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
	struct s_list	*envir;
	char	*file;			//redirnode
	int		mode;
	int		fd;
	char	*delim;			//herenode
}	t_node;

t_node	*heredoc_cmd(t_token *token);
t_node	*redir_cmd(t_token *token);
t_node	*pipe_cmd(t_token **left_list, t_token **right_list, t_list *envir);
t_node	*parse_redir(t_node *cmd, t_token **toklist);
t_node	*init_node(t_list *envir);
void	add_attribute(t_node *node, char *str);
t_node	*parse_exe(t_token **toklist, t_list *envir);
t_node	*parse_pipe(t_token **toklist, t_list *envir);
void	print_tree(t_node *tree);		// to be deleted for final vers
void	run_tree(t_node *tree, t_list **envir);
void	clear_tree(t_node *tree);
void	panic(char *msg);
int		syntax_check(t_token *toklist);
t_list	*get_env(char **envp);
void	print_env(t_list *envlist);
char	**conv_env(t_list *envir);
char	*find_exec(char *exec_file, char *path_var);
char    *search_env(char *key, t_list *envir);
void    del_arr(char **arr);
int		is_path(char *str);		// todo
char	*exp_rel_path(char *exec_file, t_list *envir);	// todo
void	write_to_pipe(int pfd[2], t_node *node);
void	reset_stdin(void);
void	run_builtin_tree(t_node *tree, t_list **envir);
//int		is_builtin(char *exec_file);					// todo
//void	run_builtin(char **param, t_list *envir);			// todo

#endif
