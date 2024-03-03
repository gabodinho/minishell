/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:32:23 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/22 22:10:15 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *) s1)[i] != ((unsigned char *) s2)[i])
			return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
    // declaring two same string
    char* first_str = "teste";
    char* second_str = "teste";
  
    // printing the strings
    printf("First String: %s\n", first_str);
    printf("Second String: %s\n", second_str);

    // printing the return value of the strncmp()
    printf("Return value of strncmp(): %d\n",
           memcmp(first_str, second_str, 1));
    printf("Return value of ft_strncmp(): %d",
           ft_memcmp(first_str, second_str, 1));

    return 0;
}
*/
