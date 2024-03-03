/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:40:25 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/23 16:37:26 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	len_li;

	len_li = ft_strlen((char *) little);
	if (len_li == 0)
		return ((char *) big);
	else if (!*big)
		return (0);
	while (big && len > 0)
	{
		if (0 == ft_strncmp(big, little, len_li) && len >= len_li)
			return ((char *) big);
		big++;
		len--;
	}
	return (0);
}
/*
int main()
{
    // declaring two equal strings
    char dest[] = "Halltsto mein lietesbertest";
    char dest2[] = "Halltsto mein lietesbertest";
    char dest3[] = "Halltsto mein lietesbertest";
	char src[] = "llt";
  
    // printing the strings
    printf("First String: %s\n", dest);
    printf("Second String: %s\n", src);

    // printing the return value of the strstr()
//    printf("Return value of strstr(): %s\n", strnstr(dest, src, 5));
    printf("Return value of ft_strstr(): %s\n", ft_strnstr("", "xx", -1));
//	printf("Return value of ft_strstr1(): %s", ft_strnstr1(dest3, src, 5));

    return 0;
}
*/
