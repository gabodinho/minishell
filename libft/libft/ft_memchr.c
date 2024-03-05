/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:39:12 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/16 21:41:26 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long	idx;

	idx = 0;
	while (idx < n)
	{
		if (*(unsigned char *) s == ((unsigned char) c))
			return ((void *) s);
		idx++;
		s++;
	}
	return (0);
}
/*
int	main(void)
{
	char str[] = "du mieser wichser!";
	write(1, (char *) ft_memchr(str, 105, 7), 10);
	return (0);
}
*/
