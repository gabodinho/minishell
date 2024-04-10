/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers_0.c.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:53:29 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 13:28:09 by irivero-         ###   ########.fr       */
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

char	**empty_str(char **arr)
{
	int		count;
	char	**stripped_arr;
	int		i;

	count = non_empty_str(arr);
	stripped_arr = malloc(sizeof(char *) * (count + 1));
	if (!stripped_arr)
		return (NULL);
	i = 0;
	while (*arr)
	{
		if (**arr != '\0')
		{
			stripped_arr[i] = ft_strdup(*arr);
			i++;
		}
		arr++;
	}
	stripped_arr[i] = NULL;
	return (stripped_arr);
}

void	export_one(char **arr, t_list **env_list)
{
	char	*var[2];
	char	*val;
	char	*str;

	var[0] = arr[0];
	var[1] = 0;
	val = ft_strdup(arr[1]);
	if (val == NULL)
		val = ft_strdup("");
	str = ft_strjoin(var[0], "=");
	str = join_and_free(str, val);
	unset_env_list(env_list, var);
	ft_lstadd_back(env_list, ft_lstnew(str));
}

int	process_export_argument(char **arr, t_list **env_list)
{
	int	exit_status;

	exit_status = 0;
	if (!is_start_valid(arr[0][0]) || !is_char_valid(arr[0]))
	{
		error_msg_export(arr[1], " : not a valid identifier");
		exit_status = 1;
	}
	else
		export_one(arr, env_list);
	return (exit_status);
}
