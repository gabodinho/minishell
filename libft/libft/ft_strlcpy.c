/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:11:31 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/22 19:13:43 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
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
	return (ft_strlen((char *) src));
}
/*
int main(void)
{
    char    source1[] = "Teststring to be copied...";
	char	source2[] = "Teststring to be copied...";
    char    destination1[10];
	char	destination2[10];  
	int len1 = strlcpy(destination1, source1, 4);
	int len2 = ft_strlcpy(destination2, source2, 4);
	printf("Original output: %d\n", len1);
	printf("My output: %d\n", len2);
	printf("Original copied string: %s\n", destination1);
	printf("My copied string: %s\n", destination2);
    return (0);
}
*/
