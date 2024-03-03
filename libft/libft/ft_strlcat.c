/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:22:56 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/06/03 00:54:39 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	size_dst;

	i = 0;
	j = 0;
	size_dst = ft_strlen(dst);
	while (dst[i] && i < size)
		i++;
	while (src[j] && size > j + i + 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i == size)
		return (ft_strlen(src) + size);
	else
	{
		dst[i + j] = 0;
		return (size_dst + ft_strlen(src));
	}
}
/*
int	main(void)
{
	char dst[] = "CCCCC";
	char str[] = "AAAAAAAAA";
	unsigned long s;	
	unsigned long size = -1;
	//s = strlcat(dst, str, size);
	printf("%s\n", dst);
	s = ft_strlcat(dst, str, size);
	printf("ft_strlcat\n input: %zu, return val: %zu\ndst1: %s",size,  s, dst);
	return (0);
}
*/
