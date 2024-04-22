/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:38:03 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/22 10:39:25 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	export_one2(char *str, t_list **envir)
{
	int		eq;
	t_list	*env;

	env = *envir;
	eq = get_equal(str);
	while (env && ft_strncmp(env -> content, str, eq))
		env = env -> next;
	if (!env)
		ft_lstadd_back(envir, ft_lstnew(ft_strdup(str)));
	else
	{
		free(env -> content);
		env -> content = ft_strdup(str);
	}
}

static int	is_valid_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	else
		return (0);
}

static int	export_syntax(char *str)
{
	int	eq;
	int	i;

	eq = get_equal(str);
	if (eq == 0)
		return (1);
	if (get_equal(str) == -1)
		eq = ft_strlen(str);
	i = 0;
	while (i < eq)
	{
		if (!is_valid_char(str[i]))
			return (1);
		i++;
	}
	if (get_equal(str) == -1)
		return (-1);
	return (0);
}

int	export_builtin(char **av, t_list **env_list)
{
	int	i;
	int	j;
	int	exit_status;

	i = 1;
	j = non_empty_str(av);
	exit_status = 0;
	if (j == 1 || av == NULL)
		return (export_all_env_vars(env_list));
	while (av[i] != NULL)
	{
		if (export_syntax(av[i]) > 0)
		{
			exit_status = 1;
			error_msg_export(av[i], " not a valid identifier");
		}
		else if (export_syntax(av[i]) == 0)
			export_one2(av[i], env_list);
		i++;
	}
	return (exit_status);
}
