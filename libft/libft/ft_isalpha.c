/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:34:13 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/21 02:02:50 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c < 65 || c > 122 || (c > 90 && c < 97))
		return (0);
	else
		return (1);
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
    res = ft_isalpha(source);
    printf("%d", ft_isalpha(source));
    return (0);
}
*/
