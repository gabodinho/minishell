/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:06:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/02 10:24:56 by irivero-         ###   ########.fr       */
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

int	print_env_without_options(char **av, t_list *env)
{
	if (!has_options(av))
	{
		print_env(env);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: env: no options allowed\n", 2);
		return (1);
	}
}
