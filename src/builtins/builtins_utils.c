/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:02:46 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/18 13:45:33 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*b_strlcpy(char *src)
{
	int		j;
	char	*tmp;

	if (!src)
		return (NULL);
	tmp = malloc(b_strlen(src) + 1);
	j = 0;
	while (src && src[j])
	{
		tmp[j] = src[j];
		j++;
	}
	tmp[j] = '\0';
	free(src);
	return (tmp);
}

int	b_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	b_putstr(char *s)
{
	write(1, s, ft_strlen(s));
	return (0);
}

int	b_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (-1);
	return (i);
}

int	b_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	var_finder(char **env, char *s)
{
	int	i;

	i = 0;
	if (!*s)
		return (-1);
	while (env[i] != NULL)
	{
		if (b_strcmp(env[i], s) == 0)
			return (i);
		i++;
	}
	return (-1);
}