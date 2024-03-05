/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 02:58:31 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/20 03:10:07 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}
/*
int main(void)
{
	char test[] = "this is a test string";

	char *ptr = test;
	while (*ptr)
	{
		ft_putchar_fd(*ptr, 1);
		ptr++;
	}
	return (0);
}
*/
