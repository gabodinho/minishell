/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:29:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/09 16:44:53 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free, exit, getenv
#include <unistd.h> //getcwd, chdir, fork, execve, wait, write, read, pipe, dup, dup2, close, isatty, ttyname, ttyslot, unlink
#include <string.h> // strerror, perror
#include <sys/wait.h> // waitpid, wait3, wait4
#include <sys/stat.h> // stat, lstat, fstat, access, open, read, close
#include <fcntl.h> // open, read, close, access
#include <errno.h>
#include <readline/readline.h> // readline
#include <readline/history.h> // history
#include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
#include <dirent.h> // opendir, closedir, readdir
#include <sys/ioctl.h> // ioctl
#include <termios.h> // tcgetattr, tcsetattr
#include <ncurses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

#endif