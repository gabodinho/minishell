/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 00:40:09 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/01 15:57:02 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_printf.h"

int	get_size_dec(t_fm *fm, long arg, char flag)
{
	int	digits;

	digits = ft_getdig(arg, 10);
	if (fm -> precision >= digits)
	{
		digits = fm -> precision;
		if (arg < 0)
			digits++;
	}
	if (arg >= 0 && fm -> spaceplus)
		digits++;
	if (!arg && !fm -> precision)
		digits = 0;
	if (digits > fm -> width || flag)
		return (digits);
	else
		return (fm -> width);
}

void	reverse_str(char *dest, int size, t_fm *fm)
{
	size_t	i;
	char	buff;

	i = 0;
	while (i < size - i)
	{
		buff = dest[i];
		dest[i] = dest[size - i - 1];
		dest[size - i - 1] = buff;
		i++;
	}
	if (fm -> zerominus != '-')
	{
		memmove(dest + ft_strlen(dest) - size, dest, size);
		i = 0;
		while (i < ft_strlen(dest) - size)
		{
			dest[i] = ' ';
			i++;
		}
	}
	return ;
}

size_t	ft_getdig_hex(unsigned long n)
{
	unsigned long	digits;

	digits = 1;
	while (n / 16 > 0)
	{
		n = n / 16;
		digits++;
	}
	return (digits);
}
