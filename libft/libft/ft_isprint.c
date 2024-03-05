/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:34:13 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/21 02:01:56 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
/*
int main(int argc, char *argv[])
{	
	if (argc > 2)
	{
		printf("too many input parameters");
		return (0);
	}
	char source = *argv[1];
	int res;
    printf("source is: %c\n", source);
    res = ft_isprint(source);
    printf("%d", ft_isalpha(source));
    return (0);
}
*/
