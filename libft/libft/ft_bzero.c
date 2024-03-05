/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:04:51 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/10 00:16:07 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned long	count;
	char			*ptr;

	count = 0;
	ptr = (char *) s;
	while (count < n)
	{
		ptr[count] = 0;
		count++;
	}
}
/*
int main(void)
{
	char source[] = "GHDGFDtstsr";
	printf("source is: %s\n", source);
    ft_bzero(source, 5);
    write(1, source, 10);
    return (0);
}
*/
