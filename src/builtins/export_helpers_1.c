/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:19:24 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 13:29:44 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	parse_export_argument(char *arg, char **arr)
{
	char	**temp;

	if (ft_strcmp(arg, "=") == 0)
	{
		error_msg_export("=", "not a valid identifier");
		return ;
	}
	temp = ft_split(arg, '=');
	if (temp[0])
		arr[0] = ft_strdup(temp[0]);
	if (temp[1])
		arr[1] = ft_strdup(temp[1]);
	free_arr(temp, get_arg_count(temp));
}

int	handle_export_without_equal_sign(void)
{
	error_msg_export("=", " : not a valid identifier");
	return (1);
}

int	handle_export_with_equal_sign(char *arg, char *equal_sign,
	t_list **env_list)
{
	char	*variable_name;
	char	*value;

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
	return (0);
}
