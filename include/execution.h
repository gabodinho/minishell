/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:25:38 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/04 12:46:16 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ft_printf.h"
# include "structs.h"
# include "tokenizer.h"
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> //getcwd, chdir, fork, execve, wait, write, read, pipe, dup, dup2, close, isatty, ttyname, ttyslot, unlink
# include <string.h> // strerror, perror
# include <sys/wait.h> // waitpid, wait3, wait4
# include <sys/stat.h> // stat, lstat, fstat, access, open, read, close
# include <fcntl.h> // open, read, close, access
# include <errno.h>
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h> // opendir, closedir, readdir
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcgetattr, tcsetattr
# include <ncurses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// exec_utils
int		is_path(char *str);
void	reset_stdin(void);
void	reset_stdout(void);
char	*find_exec(char *exec_file, char *path_var);
int		is_builtin_exec(t_node *tree);
// exec_heredoc
void	run_here(t_node *node, t_data *data, int is_builtin);
// exec_pipe
void	run_pipe(t_node *node, t_data *data);
// exec_redir
void	run_redir(t_node *node, t_data *data, int is_builtin);
// exec_exec
void	run_exec(t_node *node, t_data *data);
// exec_tree
void	run_tree(t_node *tree, t_data *data);
int		run_builtin_tree(t_data *data);
// exec_builtins
bool	is_builtin(char *str);
int		exec_builtins(char **av, t_data *data);

#endif
