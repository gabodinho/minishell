/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:20:14 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/18 18:13:58 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"
#include "parser.h"

static int	count_param(char **av)
{
	int	i;

	i = 0;
	if (!av)
		return (0);
	while (*av++)
		i++;
	return (i);
}

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

int	exec_some_builtins(char **av, t_data *data)
{
	if (ft_strcmp(av[0], "echo") == 0)
		return (our_echo(av));
	else if (ft_strcmp(av[0], "cd") == 0)
	{
		if (count_param(av) > 2)
		{
			printf("minishell: cd: too many arguments\n");
			return (1);
		}
		else
			return (our_cd(av, *(data -> envir)));
	}
	return (0);
}

int	exec_builtins(char **av, t_data *data)
{
	char	**keys;
	int		status;

	status = 0;
	if (ft_strcmp(av[0], "pwd") == 0)
		return (our_pwd(av, 0, *data -> envir));
	if (ft_strcmp(av[0], "export") == 0)
		return (export_builtin(av, data -> envir));
	if (ft_strcmp(av[0], "env") == 0)
		return (print_env_without_options(av, *(data -> envir)));
	if (ft_strcmp(av[0], "unset") == 0)
	{
		if (av[1] != NULL)
		{
			keys = av + 1;
			unset_env_list(data -> envir, keys);
		}
		return (0);
	}
	if (ft_strcmp(av[0], "exit") == 0)
		exit_command(av, data);
	else
		return (exec_some_builtins(av, data));
	if (status != 0)
		return (status);
	return (1);
}
