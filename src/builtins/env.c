/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:06:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/11 23:07:00 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	has_options(char **av)
{
	int	i;

	i = 1;
	while (av[i] != NULL)
	{
		if (av[i][0] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	print_env_with_arg_error(char *arg)
{
	char	*error_message;

	error_message = ft_strjoin("minishell: env: ", arg);
	if (error_message)
	{
		ft_putstr_fd(error_message, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(error_message);
	}
	else
		perror("minishell: env");
	return (127);
}

int	print_env_without_options(char **av, t_list *env)
{
	if (!has_options(av))
	{
		if (av[1] != NULL)
			return (print_env_with_arg_error(av[1]));
		else
		{
			print_env(env);
			return (0);
		}
	}
	else
	{
		ft_putstr_fd("minishell: env: no options allowed\n", 2);
		return (1);
	}
}
