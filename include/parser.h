/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:25:38 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/15 13:56:23 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_printf.h"
# include "structs.h"
# include "tokenizer.h"
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h>
# include <sys/wait.h> // waitpid, wait3, wait4
# include <sys/stat.h> // stat, lstat, fstat, access, open, read, close
# include <fcntl.h> // open, read, close, access
# include <errno.h>
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h> // opendir, closedir, readdir
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcgetattr, tcsetattr
# include <ncurses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// parse_exe.c
t_node	*parse_exe(t_token **toklist, t_list *envir);
// parse_pipe.c
t_node	*parse_pipe(t_token **toklist, t_list *envir);
// parse_redir.c
t_node	*parse_redir(t_node *cmd, t_token **toklist);
// parse_utils.c
void	panic(char *msg, int ret);
int		syntax_check(t_token *toklist, int print_err);
void	clear_tree(t_node *tree);
t_node	*add_last(t_node *redir, t_node *exec);
// environment.c
t_list	*get_env(char **envp);
void	print_env(t_list *envlist);
char	**conv_env(t_list *envir);
char	*search_env(char *key, t_list *envir);
void	del_arr(char **arr);

#endif
