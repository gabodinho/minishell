/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:12 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/25 15:02:06 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	get_arg_count(char **argv)
{
	int	len;

	len = 0;
	if (!argv)
		return (len);
	while (argv[len])
		len ++;
	return (len);
}

void	free_arr(char **env, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(env[i]);
		env[i] = NULL;
		i ++;
	}
	free(env);
	env = NULL;
}

void	handle_export(char *arg, t_list **env_list)
{
	char	**arr;

	arr = ft_split(arg, '=');
	if (arr[0])
		arr[0] = remove_one_quote_set(arr[0]);
	if (arr[1])
		arr[1] = remove_one_quote_set(arr[1]);
	if (!is_valid_var_start(arr[0][0]) || !is_valid_var_char(arr[0]))
	{
		g_exit_status = 1;
		print_export_error(arr[0], arr[1], " : not a valid identifier");
	}
	else
		export_one_var(arr, env_list);
	free_arr(arr, get_arg_count(arr));
}

void	export_builtin(char **args, t_list **env_list)
{
	int		i;

	g_exit_status = 0;
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '='))
			handle_export(args[i], env_list);
		i++;
	}
}
