/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:33:38 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/20 02:56:26 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned long	idx;

	idx = 0;
	while (s[idx])
	{
		f(idx, &s[idx]);
		idx++;
	}
	return ;
}
/*
void    ft_capitalize(unsigned int i, char *c)
{
    if (i == 0)
    {
        if (*c >= 'a' && *c <= 'z')
            *c -= 32;
    }
    return;
}

void    ft_evnup(unsigned int i, char *c)
{
    if (i%2 == 0)
    {
        if (*c >= 'a' && *c <= 'z')
            *c -= 32;
    }
    return;
}

int main(void)
{
	char test[] = "this is a test string";
	ft_striteri(test, ft_capitalize);
	printf("%s", test);
	ft_striteri(test, ft_evnup);
	printf("\n%s", test);
	return (0);
}
*/
