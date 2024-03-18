/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:33 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/18 14:18:41 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parser.h"

void	exit_command(char **av)
{
	int	exit_status;

	ft_putendl_fd("exit", 2);
	if (av[1] == NULL)
		exit (g_exit_status);
	exit_status = ft_atoi(av[1]);
	if (ft_strlen(av[1]) > 3 || exit_status < 0 || exit_status > 255)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putendl_fd("numeric argument required", 2);
		exit(255);
	}
	if (av[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	else
		exit (exit_status);
}