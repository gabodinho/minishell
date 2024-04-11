/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:20:14 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 16:04:47 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"
#include "parser.h"

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

int	exec_builtins(char **av, t_data *data)
{
	char	**keys;

	if (ft_strcmp(av[0], "echo") == 0)
		return (our_echo(av));
	if (ft_strcmp(av[0], "cd") == 0)
		return (our_cd(av, *(data -> envir)));
	if (ft_strcmp(av[0], "pwd") == 0)
		return (our_pwd(av, 0));
	if (ft_strcmp(av[0], "export") == 0)
		return (export_builtin(av, data -> envir));
	if (ft_strcmp(av[0], "env") == 0)
		return (print_env(*(data -> envir)), 0);
	if (ft_strcmp(av[0], "unset") == 0)
	{
		if (av[1] != NULL)
		{
			keys = av + 1;
			unset_env_list(data -> envir, keys);
		}
		return (0);
	}
	else
		exit_command(av, data);
	return (1);
}