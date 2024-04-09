/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:33 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/02 10:28:03 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec_b.h"
#include "parser.h"

void	exit_command(char **av, t_data *data)
{
	int	exit_status;

	if (has_options(av))
	{
		ft_putstr_fd("minishell: exit: no options allowed\n", 2);
		return ;
	}
	ft_putendl_fd("exit", 2);
	if (av[1] != NULL)
	{
		exit_status = ft_atoi(av[1]);
		if (ft_strlen(av[1]) > 3 || exit_status < 0 || exit_status > 255)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putendl_fd("numeric argument required", 2);
			clear_list(data -> tok_lst);
			ft_lstclear(data -> envir, free);
			clear_tree(data -> tree);
			free(data);
			exit(255);
		}
		if (av[2] != NULL)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return ;
		}
		else
		{
			clear_list(data -> tok_lst);
			ft_lstclear(data -> envir, free);
			clear_tree(data -> tree);
			free(data);
			exit (exit_status);
		}
	}
	else
	{
		clear_list(data -> tok_lst);
		ft_lstclear(data -> envir, free);
		clear_tree(data -> tree);
		free(data);
		exit(0);
	}
}
