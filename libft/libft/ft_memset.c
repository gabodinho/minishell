/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:04:51 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/16 21:09:28 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned long	count;

	count = 0;
	while (count < n)
	{
		((char *) s)[count] = c;
		count++;
	}
	return (s);
}
/*
int main(int argc, char *argv[])
{	
	if (argc > 2)
	{
		printf("too many input parameters");
		return (0);
	}
	char source = *argv[1];
	char *res;
	void *ptr;
	printf("source is: %c\n", source);
    res = (char *)ft_memset(&ptr, source, 5);
    write(1, res, 10);
    return (0);
}
*/
