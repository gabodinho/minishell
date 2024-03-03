/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:50:12 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/25 03:07:47 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
/*
int main(void)
{
    char source[] = "GHDGFDtstsr";
    printf("source is: %s\n", source);
    char *ptr = ft_calloc(1, 5);
	ptr[1] = 'r';
	ptr[4] = 'e';
	write(1, ptr, 10);
    return (0);
}
*/
