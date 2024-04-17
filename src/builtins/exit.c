/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:33 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/17 14:32:07 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"
#include "parser.h"

int	get_exit_status_cmd(char **av)
{
	int	exit_status;

	if (av[1] != NULL)
	{
		exit_status = ft_atoi(av[1]);
		if (ft_strlen(av[1]) > 3 || exit_status < 0 || exit_status > 255)
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			return (255);
		}
		if (av[2] != NULL)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		return (exit_status);
	}
	return (0);
}

void	exit_command(char **av, t_data *data)
{
	int	exit_status;

	if (data->tree->ntype != N_PIPE)
		ft_putendl_fd("exit", 2);
	if (has_options(av) || ft_isalpha(ft_atoi(av[1])))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit_with_cleaup(data, 255);
	}
	exit_status = get_exit_status_cmd(av);
	if (av[1] && av[2] != NULL && exit_status == 1)
		return ;
	exit_with_cleaup(data, exit_status);
}
