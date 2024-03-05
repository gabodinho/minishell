/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:41:48 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/07/24 22:11:45 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned long	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}
/*
int main(void)
{
    printf("%zu", ft_strlen("This string is supposed to be counted..."));
    return (0);
}
*/
