/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 03:13:59 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/26 04:14:52 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;

	if (ft_strlen(s) > start)
	{
		if (start + len > ft_strlen(s) || len > ft_strlen(s))
			str = malloc(ft_strlen(s) - start + 1);
		else
			str = malloc(len + 1);
		if (!str)
			return (str);
	}
	else
	{
		str = malloc(1);
		str[0] = 0;
		return (str);
	}
	if (len > len + 1)
		ft_strlcpy(str, &s[start], len);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}
/*
int main(void)
{
	char str[] = "hola";
	char *ptr = ft_substr(str, 0, 18446744073709551615);
	printf("%p", ptr);
	return (0);
}
// what if string finishes before reaching len?
// does len include the nullterminator?
*/
