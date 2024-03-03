/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:33:38 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/25 02:49:56 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned long	len;
	unsigned long	idx;
	char			*res;

	len = ft_strlen(s);
	res = malloc(len + 1);
	if (!res)
		return (0);
	idx = 0;
	while (s[idx])
	{
		res[idx] = f(idx, s[idx]);
		idx++;
	}
	res[idx] = 0;
	return (res);
}
/*
char    ft_capitalize(unsigned int i, char c)
{
    if (i == 0)
    {
        if (c >= 'a' && c <= 'z')
            c -= 32;
    }
    return (c);
}

char    ft_evnup(unsigned int i, char c)
{
    if (i%2 == 0)
    {
        if (c >= 'a' && c <= 'z')
            c -= 32;
    }
    return (c);
}
int main(void)
{
	char test[] = "this is a test string";
	char *res2 = ft_strmapi(test, ft_capitalize);
	char *res = ft_strmapi(test, ft_evnup);
	printf("%s", res);
	printf("\n%s", res2);
	return (0);
}
*/
