/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:20:14 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/18 15:51:12 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_b.h"

bool	is_builtin(char *str)
{
	if (!str)
		return (false);
	if (!ft_strcmp(str, "echo") 
		|| !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "exit"))
		return (true);
	return (false);
}

int	exec_builtins(char **av, t_list *env)
{
	if (ft_strcmp(av[0], "echo") == 0)
		return (our_echo(av), 0);
	if (ft_strcmp(av[0], "cd") == 0)
		return (our_cd(av, env), 0);
	if (ft_strcmp(av[0], "pwd") == 0)
		return (our_pwd(av, 0), 0);
	if (ft_strcmp(av[0], "export") == 0)
		return (export_builtin(av, &env), 0);
	if (ft_strcmp(av[0], "env") == 0)
		return (print_env(env), 0); //change env.c
	if (ft_strcmp(av[0], "unset") == 0)
		return (unset_env_list(&env, av[1]), 0); //change
	exit_command(av);
	return (1);
}
	