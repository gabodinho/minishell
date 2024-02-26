/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:29:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/26 12:39:08 by irivero-         ###   ########.fr       */
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
# define DLESS 3
# define DGREAT 4
# define LESS 5
# define GREAT 6
//# define HEREDOC 4
# define DOUBLE_QUOTES 7
# define SINGLE_QUOTES 8

//estructura para un token
typedef struct	s_token 
{
	int				type; // tipo de token 
	char			*str; // cadena asociada al token
	struct s_token	*next; // siguiente token
	struct s_token	*prev; // token anterior
	
} t_token;

typedef struct	s_envp
{
	char	**envp;
	char 	*cd_hist;
} t_envp;

extern int	g_exit_status;

int	main();

//new_tokenizer
t_token	*tokenizer(void);
t_token	*tokenize_line(char *line);
t_token	*create_token(char *content, int type);
void	token_lst_add_back(t_token **token_lst, t_token *new);
int		is_space(char c);
void	skip_spaces(char **str);
int		is_quotes(char c);
bool	skip_quotes(char *line, size_t  *i);
int		is_shell_separator(char *c);
void	clear_list(t_token **token_lst);
int		add_separator_token(int type, char **line, t_token **token_lst);
int		process_command(char **line, t_token **token_lst);

//libft
char *ft_substr(char *s, unsigned int start, size_t len);
int ft_strncmp(char *s1, char *s2, size_t n);
char *ft_strchr(char *s, int c);

/*tokenizer
int ft_strcmp(const char *s1, const char *s2);
int is_redirections(const char *str);
int is_space(char c);
int find_quotes(const char *line, int i, char quote_char);
int single_quotes(const char *line, int i);
int double_quotes(const char *line, int i);
int quotes_end(const char *line, int i, t_token *token);
void assign_token_types(t_itokens *itokens);
void count_tokens(char *str, int *i, int *size);
int counter_simplified(char *str);
// char	*ft_substr(const char *str, int start, int length);
// char	*ft_strndup(const char *str, size_t n);
void process_token_char(int *i, const char *str, t_token *token, int *token_idx);
t_token *tokenize_and_build_array(const char *str, t_token *token, int max);
int split_token(char *str, t_itokens *itokens);
void free_tokens(t_itokens *itokens);
int error_malloc(void);
*/
#endif