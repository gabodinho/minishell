/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:49:25 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 13:52:20 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	is_envirom(char *str, int i)
{
	if (str[i] == '$')
	{
		if (str[i + 1] == '$')
			return (0);
		if (str[i + 1] == '\0')
			return (0);
		if (ft_isalpha(str[i + 1]))
			return (1);
		if (str[i + 1] == '?')
			return (1);
		if (str[i + 1] == '_')
			return (1);
	}
	return (0);
}

int	is_env_char(char c)
{
	if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
		return (1);
	else
		return (0);
}

int	is_token_in_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_envirom(str, i))
			return (i);
		i++;
	}
	return (-1);
}

int	find_dollar(char *str, int i)
{
	if (str[i] == '?')
		return (i);
	while (is_env_char(str[i]))
		i++;
	return (i - 1);
}
