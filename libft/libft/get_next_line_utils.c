/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:42:14 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/02 21:10:22 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (gnl_strlen((char *) src));
}

int	get_idx(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	i = 0;
	len = gnl_strlen(str);
	while (str[i] != '\n' && i < len)
		i++;
	if (str[i])
		return (i + 1);
	else
		return (0);
}

char	*shift_previous(char *previous)
{
	int		i;
	int		idx;
	char	*res;

	idx = get_idx(previous);
	if (idx)
	{
		res = malloc(sizeof(char) * (gnl_strlen(previous + idx) + 1));
		if (!res)
			return (0);
		i = 0;
		while (previous[i + idx])
		{
			res[i] = previous[i + idx];
			i++;
		}
		res[i] = 0;
		free(previous);
	}
	else
	{
		free(previous);
		res = 0;
	}
	return (res);
}

char	*get_linee(char *previous)
{
	int		idx;
	char	*res;

	if (!*previous)
		return (0);
	idx = get_idx(previous);
	if (!idx)
		idx = gnl_strlen(previous);
	res = malloc(sizeof(char) * (idx + 1));
	if (!res)
		return (0);
	gnl_strlcpy(res, previous, idx + 1);
	return (res);
}
