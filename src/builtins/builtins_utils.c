/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:02:46 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/01 10:05:32 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_start_valid(unsigned char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}

int	is_char_valid(char *var)
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
