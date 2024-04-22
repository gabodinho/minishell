/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:06:10 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/22 10:38:30 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error_msg_export(char *arg, char *message)
{
	ft_putstr_fd("minishell: export: '", 2);
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		if (message != NULL)
		{
			ft_putstr_fd("'", 2);
			ft_putstr_fd(message, 2);
		}
	}
	ft_putstr_fd("\n", 2);
}

int	non_empty_str(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (count);
	while (*arr)
	{
		if (**arr != '\0')
			count++;
		arr++;
	}
	return (count);
}

void	print_env_declare(t_list *envlist)
{
	while (envlist)
	{
		printf("declare -x ");
		printf("%s\n", (char *) envlist -> content);
		envlist = envlist -> next;
	}
}

int	export_all_env_vars(t_list **env_list)
{
	print_env_declare(*env_list);
	return (0);
}

int	get_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (-1);
	else
		return (i);
}
