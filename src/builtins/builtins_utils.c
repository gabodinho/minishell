/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:02:46 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/28 15:01:07 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export_error(char *var, char *val, char *message)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putchar_fd('=', 2);
	ft_putstr_fd(val, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	is_valid_var_start(unsigned char c)
{
	if (ft_isalnum(c) || c == '_' || c != '=')
		return (1);
	else
		return (0);
}

int	is_valid_var_char(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0')
	{
		if (!(ft_isalpha((unsigned char)var[i]) || var[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*remove_one_quote_set(char *str)
{
	size_t	end;

	end = ft_strlen(str) - 1;
	if (str[0] == '\'' && str[end] == '\'')
		str = ft_strtrim(str, "\'");
	else if (str[0] == '\"' && str[end] == '\"')
		str = ft_strtrim(str, "\"");
	return (str);
}

void	export_one_var(char **arr, t_list **env_list)
{
	char	*var;
	char	*val;
	char	*str;

	var = arr[0];
	val = arr[1];
	if (val == NULL)
		val = ft_strdup("");
	str = ft_strjoin(var, ft_strdup("="));
	str = ft_strjoin(str, val);
	unset_env_list(env_list, var);
	ft_lstadd_back(env_list, ft_lstnew(str));
}
