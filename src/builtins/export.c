/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:12 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 13:29:37 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	handle_export(char **argv, int i, t_list **env_list)
{
	char	*arg;
	char	*equal_sign;

	arg = argv[i];
	equal_sign = ft_strchr(arg, '=');
	if (arg && equal_sign)
		return (handle_export_with_equal_sign(arg, equal_sign, env_list));
	else
		return (handle_export_without_equal_sign());
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

int	process_export_arg(char **av, int *index, t_list **env_list)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strchr(av[*index], '='))
	{
		if (ft_strcmp(av[*index], "=") != 0)
			exit_status |= handle_export(av, *index, env_list);
		else if (av[*index + 1] != NULL)
			exit_status |= handle_export(av, ++(*index), env_list);
	}
	return (exit_status);
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
	else
	{
		while (av[i] != NULL)
		{
			exit_status |= process_export_arg(av, &i, env_list);
			i++;
		}
	}
	return (exit_status);
}

/*
int	export_builtin(char **av, t_list **env_list)
{
	int	i;
	int	j;
	int	exit_status;

	i = 1;
	j = non_empty_str(av);
	exit_status = 0;
	if (j == 1 || av == NULL)
	{
		print_env_declare(*env_list);
		return (exit_status);
	}
	else
	{
		while (av[i] != NULL)
		{
			if (ft_strchr(av[i], '='))
			{
				if (ft_strcmp(av[i], "=") != 0)
					exit_status |= handle_export(av, i, env_list);
				else if (av[i + 1] != NULL)
					exit_status |= handle_export(av, ++i, env_list);
			}
			i++;
		}
	}
	return (exit_status);
}*/
/*
int	export_builtin(char **argv, t_list **env_list)
{
	int		count;
	char	**arr;
	int		exit_status;

	count = non_empty_str(argv);
	arr = empty_str(argv);
	exit_status = 0;
	if (count == 1 || arr == NULL)
		print_env_declare(*env_list);
	else if (count == 2 && arr != NULL)
	{
		if (ft_strchr(arr[1], '='))
		{
			exit_status = 0;
			handle_export(arr, env_list);
		}
		else if (!is_start_valid(arr[1][0]) || !is_char_valid(arr[1]))
		{
			exit_status = 1;
			error_msg_export(arr[1], " : not a valid identifier");
		}
	}
	else
	{
		exit_status = 0;
		handle_export(arr, env_list);
	}
	free_arr(arr, count);
	return (exit_status);
}
*/

/*
int	handle_export(char **argv, int i, t_list **env_list)
{
	char	*arg;
	char	*equal_sign;
	char	*variable_name;
	char	*value;

	arg = argv[i];
	equal_sign = ft_strchr(arg, '=');
	if (arg && equal_sign)
	{
		while (*arg == ' ')
			arg++;
		if (*arg == '\0' || *arg == '=')
		{
			error_msg_export(arg, ": not a valid identifier");
			return (1);
		}
		variable_name = ft_substr(arg, 0, equal_sign - arg);
		value = equal_sign + 1;
		if (!is_char_valid(variable_name))
		{
			printf("minishell: export: '%s' : not a valid identifier\n",
				variable_name);
			free(variable_name);
			return (1);
		}
		export_one((char *[]){variable_name, value}, env_list);
		free(variable_name);
	}
	else
	{
		error_msg_export("=", ": not a valid identifier");
		return (1);
	}
	return (0);
}*/