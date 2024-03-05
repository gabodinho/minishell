/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:33:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/25 03:00:52 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getword(char const *s, char c)
{
	unsigned long	len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static size_t	ft_nwords(char const *s, char c)
{
	unsigned long	n;
	int				previous;

	n = 0;
	previous = 0;
	while (*s)
	{
		if (*s != c)
			previous = 1;
		else
		{
			if (previous)
				n++;
			previous = 0;
		}
		s++;
	}
	if (previous)
		n++;
	return (n);
}

char	**ft_split(char const *s, char c)
{
	size_t	nwords;
	size_t	idx;
	size_t	lword;
	char	**res;

	nwords = ft_nwords(s, c);
	idx = 0;
	res = malloc(sizeof(char *) * (nwords + 1));
	if (!res)
		return (0);
	while (idx < nwords)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			lword = ft_getword(s, c);
			res[idx] = malloc(sizeof(char) * (lword + 1));
			ft_strlcpy(res[idx], s, lword + 1);
			s += lword;
		}
		idx++;
	}
	res[idx] = 0;
	return (res);
}
/*
int main(void)
{
	const char str[] = "      split       this for   me  !       ";
	char delim = ' ';
	printf("%lu", ft_nwords(str, delim));
	char **res;
	printf("String: %s\n", str);
	printf("Delimiter: %d",(int) delim);
	
	res = ft_split(str, delim);
	
	//printf("%s", res[0]);
	while (*res)
	{
		printf("\n%s", *res);
		res++;
	}
	return (0);
}
*/
