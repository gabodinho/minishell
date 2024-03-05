/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 01:21:59 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/25 03:02:44 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*res;
	unsigned long	end;

	while (ft_strchr(set, *s1) && *s1)
		s1++;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[end]) && end > 0)
		end--;
	if (*s1 == 0)
	{
		res = malloc(1);
		res[0] = 0;
		return (res);
	}
	res = malloc(end + 2);
	if (res == 0)
		return (0);
	ft_strlcpy(res, s1, end + 2);
	return (res);
}
/*

#include <stdio.h>

int main(void)
{
	char test[] = "  \t \t \n   \n\n\n\t";
	char set[] = " \n\t";
	char *res = ft_strtrim(test, set);
	printf("%s\n%s\n%s", test, set, res);
//	printf("\n%s", *(&test + 1)	- 5);
	return (0);
}
*/
