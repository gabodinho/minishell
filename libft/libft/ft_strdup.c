/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:31:10 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/23 17:33:24 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	char	*res;

	ptr = malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (ptr);
	res = ptr;
	while (*s)
	{
		*ptr = *(char *) s;
		ptr++;
		s++;
	}
	*ptr = 0;
	return (res);
}
/*
int main(void)
{
	char test[] = "this is mz string";
	char *cpy = ft_strdup(test);
	printf("\n%s\n%s\n", test, cpy);
	return(0);
}
*/
