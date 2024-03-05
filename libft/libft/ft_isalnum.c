/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:34:13 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/21 02:02:18 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123))
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
    res = ft_isalnum(source);
    printf("%d", ft_isalnum(source));
    return (0);
}
*/
