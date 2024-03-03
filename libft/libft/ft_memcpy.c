/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:04:51 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/22 18:43:17 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long	count;

	count = 0;
	if (!dest && !src)
		return (0);
	while (count < n)
	{
		((char *) dest)[count] = ((char *) src)[count];
		count++;
	}
	return (dest);
}
/*
int main(void)
{	
	char source[] = "resrtse";
	void *dest;
	char *res = (char *) ft_memcpy(0, 0, 5);
	write(1, source, 10);
	write(1, "\n", 1);
	write(1, res, 10);
    return (0);
}
*/
