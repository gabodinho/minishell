/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:03:57 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/12 17:05:21 by irivero-         ###   ########.fr       */
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
char	**empty_str(char **arr);
void	export_one(char **arr, t_list **env_list);
int		handle_export_without_equal_sign(void);
int		handle_export_with_equal_sign(char *arg, char *equal_sign,
			t_list **env_list);
//pwd
void	if_pflag_is_one(char *path);
int		our_pwd(char **av, int pflag, t_list *env);
//unset
void	lst_rm(t_list **lst, int i);
int		unset_env_list(t_list **env_list, char **target_key);

//utils
int		is_start_valid(unsigned char c);
int		is_char_valid(char *var);
char	*remove_one_quote_set(char *str);
int		get_arg_count(char **argv);
void	free_arr(char **env, int len);

#endif
