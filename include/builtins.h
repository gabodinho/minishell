/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:03:57 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/25 15:37:20 by irivero-         ###   ########.fr       */
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

extern int	g_exit_status;

//cd
void	our_cd(char **av, t_list *env);
//echo
int		echo_helper(char **av, char *c, int *i);
void	our_echo(char **av);
//exit
void	exit_command(char **av);
//export
int		get_arg_count(char **argv);
void	free_arr(char **env, int len);
void 	export_builtin(char **builtin, t_list **env_list);
//pwd
void	if_pflag_is_one(char *path);
char	*our_pwd(char **av, int pflag);
//unset
void	lst_rm(t_list **lst, int i);
void	unset_env_list(t_list **env_list, char *target_key);

//utils
void	print_export_error(char *var, char *val, char *message);
int		is_valid_var_start(unsigned char c);
int		is_valid_var_char(char *var);
char	*remove_one_quote_set(char *str);
void	export_one_var(char **arr, t_list **env_list);


#endif