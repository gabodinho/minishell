/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:03:57 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/18 15:50:47 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "expander.h"
# include "parser.h"
# include "tokenizer.h"
# include "exec_b.h"
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
void	our_cd(char **av, t_list *env);
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
void export_env_list(t_list **env_list, char *key, char *value);
void export_builtin(char **args, t_list **env_list);
//pwd
void	if_pflag_is_one(char *path);
char	*our_pwd(char **av, int pflag);
//unset
void	lst_rm(t_list **lst, int i);
void	unset_env_list(t_list **env_list, char *target_key);

#endif