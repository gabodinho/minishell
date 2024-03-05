/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:29:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/14 17:17:54 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

//# include "libft/libft.h"

//define el tipo de token
# define T_NULL 0
# define WORD 1
# define PIPE 2
# define REDIR 3
# define DOUBLE_QUOTES 4
# define SINGLE_QUOTES 5

//estructura para un token
typedef struct	s_token 
{
	int		type; // tipo de token 
	char	*str; // cadena asociada al token
} t_token;

//almacenar info relacionada con los tokens
typedef struct	s_itoken
{
	t_token	*token; // puntero a un array de tokens
	int		size; // cantidad total de tokens
} t_itokens;

typedef struct	s_envp
{
	char	**envp;
	char 	*cd_hist;
} t_envp;

extern int	g_exit_status;

int	main();

//tokenizer
int		ft_strcmp(const char *s1, const char *s2);
int		is_redirections(const char *str);
int 	is_space(char c);
int		find_quotes(const char *line, int i, char quote_char);
int		single_quotes(const char *line, int i);
int 	double_quotes(const char *line, int i);
int 	quotes_end(const char *line, int i, t_token *token);
void	assign_token_types(t_itokens *itokens);
void	count_tokens(char *str, int *i, int *size);
int		counter_simplified(char *str);

#endif