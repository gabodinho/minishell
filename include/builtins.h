/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:03:57 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/22 10:39:21 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "structs.h"
# include "expander.h"
# include "parser.h"
# include "tokenizer.h"
# include "execution.h"

void	exit_with_cleaup(t_data *data, int exit_status);

//cd
int		our_cd(char **av, t_list *env);
//cd helpers
char	*change_directory(char *new_dir);
void	update_existing_environment_variable(t_list *env_list, const char *key,
			const char *value);
void	add_new_environment_variable(t_list **env_list, const char *key,
			const char *value);
void	update_environment_variable(t_list **env_list, const char *key,
			const char *value);
char	*get_env_var(const char *key, t_list *env_list);
int		is_path_cd(char *str);
//echo
int		our_echo(char **av);
//exit
void	exit_command(char **av, t_data *data);
//env
int		has_options(char **av);
int		print_env_without_options(char **av, t_list *env);
//export
int		export_builtin(char **argv, t_list **env_list);
//export helpers
void	error_msg_export(char *arg, char *message);
int		non_empty_str(char **arr);
int		export_all_env_vars(t_list **env_list);
int		get_equal(char *str);
//pwd
void	if_pflag_is_one(char *path);
int		our_pwd(char **av, int pflag, t_list *env);
//unset
void	lst_rm(t_list **lst, int i);
int		unset_env_list(t_list **env_list, char **target_key);

#endif
