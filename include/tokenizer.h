/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:29:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/19 15:35:51 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "ft_printf.h"
# include "structs.h"
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> 
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

# define MAX_TOKEN_LENGTH 100
# define GREEN_FOSFORITO "\033[38;5;10m"
# define RESET_COLOR "\033[0m"

//define el tipo de token
# define T_NULL 0
# define WORD 1
# define PIPE 2
# define REDIR 3

//estructura para un token
// typedef struct	s_token
// {
// 	int				type;
// 	char			*str;
// 	struct s_token	*next;
// 	struct s_token	*prev;
// } t_token;

//new_tokenizer
t_token	*tokenizer(t_list *env, char *line, int exit_status);
t_token	*tokenize_line(char *line);
t_token	*create_token(char *content, int type);
void	token_lst_add_back(t_token **token_lst, t_token *new);
int		ft_strcmp(char *s1, char *s2);
int		is_space(char c);
void	skip_spaces(char **str);
int		is_quotes(char c);
bool	skip_quotes(char *line, size_t *i);
int		is_shell_separator(char *c);
void	clear_list(t_token **token_lst);
int		add_separator_token(int type, char **line, t_token **token_lst);
int		process_command(char **line, t_token **token_lst);
void	print_token_list(t_token *token_lst); //quitar al final
int		print_quotes_error(char c);
t_token	*get_full_token_lst(t_list *envir, int exit_status);
char	*join_and_free(char *old, char *new);
void	handle_eof_error(t_token **token_lst, char *line, t_list *envir);
//main
void	welcome_message(void);
t_data	*get_data(t_token **toklst, t_list **envir, t_node *tree);

#endif
