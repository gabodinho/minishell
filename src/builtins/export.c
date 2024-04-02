/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:12 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/02 11:31:33 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	parse_export_argument(char *arg, char **arr)
{
	char	**temp;

	temp = NULL;
	if (ft_strcmp(arg, "=") != 0)
	{
		temp = ft_split(arg, '=');
		if (temp[0])
			arr[0] = ft_strdup(temp[0]);
		if (temp[1])
			arr[1] = ft_strdup(temp[1]);
		free_arr(temp, get_arg_count(temp));
	}
	else
	{
		arr[0] = ft_strdup(arg - 1);
		if (*(arg + 1) != '\0')
			arr[1] = ft_strdup(arg + 1);
	}
}

void	process_export_argument(char **arr, t_list **env_list)
{
	if (!is_start_valid(arr[0][0]) || !is_char_valid(arr[0]))
	{
		g_exit_status = 1;
		error_msg_export(arr[0], arr[2], " : not a valid identifier");
	}
	else
		export_one(arr, env_list);
}

void	handle_export(char **argv, t_list **env_list)
{
	char	*arr[3];
	int		i;

	arr[0] = NULL;
	arr[1] = NULL;
	arr[2] = NULL;
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strchr(argv[i], '='))
		{
			parse_export_argument(argv[i], arr);
			process_export_argument(arr, env_list);
		}
		i++;
	}
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
			error_msg_export(arr[1], NULL, " : not a valid identifier");
		}
	}
	else
	{
		exit_status = 0,
		handle_export(arr, env_list);
	}
	free_arr(arr, count);
	return (exit_status);
}
