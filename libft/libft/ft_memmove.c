/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:04:51 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/25 00:36:19 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned long	idx;

	idx = 0;
	if (!dest && !src)
		return (0);
	if (dest > src && dest < src + n)
	{
		while (idx < n)
		{
			((char *) dest)[n - 1] = ((char *) src)[n - 1];
			n--;
		}
	}
	else
	{
		while (idx < n)
		{
			((char *) dest)[idx] = ((char *) src)[idx];
			idx++;
		}
	}
	return (dest);
}
/*
int main(void)
{	

	char src1[] = "this is my source";
	char *dst1 = src1 + 5;
	char src2[] = "this is my source";
	char *dst2 = src2 + 5; 
	char src3[] = "this is my source";
    char *dst3 = src3 + 5;
	unsigned long n = 10;	
	memcpy(dst1, src1, n);
	memmove(dst2, src2, n);
	ft_memmove(dst3, src3, n);
	printf("after using memcpy(): %s\n", dst1);
	printf("after using memmove(): %s\n", dst2);
	printf("after using ft_memmove(): %s\n", dst3);
    return (0);
}
*/
