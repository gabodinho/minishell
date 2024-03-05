/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:32:23 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/23 16:42:26 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
    // declaring two same string
    char* first_str = "erteer";
    char* second_str = "";
  
    // printing the strings
    printf("First String: %s\n", first_str);
    printf("Second String: %s\n", second_str);

    // printing the return value of the strncmp()
    printf("Return value of strncmp(): %d\n",
           strncmp(first_str, second_str, 5));
    printf("Return value of ft_strncmp(): %d",
           ft_strncmp(first_str, second_str, 5));

    return 0;
}
*/
