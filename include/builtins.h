/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:03:57 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/14 09:20:05 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "expander.h"
# include "parser.h"
# include "tokenizer.h"
# include "../libft/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>

typedef struct	s_envp
{
	char	**envp;
	char 	*cd_hist;
} t_envp;

extern int	g_exit_status;


int	var_finder(char **env, char *s);
//cd
char	*path_finder(char **env);
char	*path_to_usr(char *path);
char	*path_filler(char **paths, t_envp *env, char *path);
char	*b_strlcpy(char *src);
void	change_directory(char **paths, t_envp *env);
//echo
int		ft_strcmp(const char *s1, const char *s2);
int		b_strcmp(char *s1, char *s2);
int		b_putstr(char *s);
int		b_strchr(char *s, char c);
int		echo_helper(char **av, char *c, int *i);
void	our_echo(char **av);
//env
int		b_strlen(char *s);
void	ft_env(t_envp *env);
//exit
void	exit_command(char **av);
//export
void	export(char **builtin, t_envp *env);
//pwd
void	if_pflag_is_one(char *path);
char	*our_pwd(char **av, int pflag);
//unset
void	ft_unset(char *v_name, t_envp *env);

int	main(void);

#endif