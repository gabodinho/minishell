/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 00:40:09 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/07/26 09:54:18 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_printf.h"

long	rdec2hex(char *dest, unsigned long arg, char flag)
{
	long	i;
	long	dec;
	int		offset;

	i = 0;
	offset = 87;
	if (flag == 'X')
		offset = 55;
	while (arg || (!arg && !i))
	{
		dec = arg % 16;
		if (dec >= 10)
			dest[i] = dec + offset;
		else
			dest[i] = dec + 48;
		arg /= 16;
		i++;
	}
	return (i);
}

char	*prep_str(size_t size)
{
	char			*ptr;
	unsigned long	count;

	ptr = malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (0);
	count = 0;
	while (count < size)
	{
		ptr[count] = ' ';
		count++;
	}
	ptr[count] = 0;
	return (ptr);
}

int	free_len(char *str)
{
	size_t	len;

	if (!str)
		len = 0;
	else
		len = ft_strlen(str);
	free(str);
	return (len);
}

size_t	ft_getdig(long long n, int base)
{
	unsigned long	digits;

	if (n < 0)
	{
		digits = 2;
		n = n * (-1);
	}
	else
		digits = 1;
	while (n / base > 0)
	{
		n = n / base;
		digits++;
	}
	return (digits);
}

int	add_prefix(char *dest, t_fm *fm, int sign)
{
	if (sign == -1)
	{
		*dest = '-';
		return (1);
	}
	else if (sign == 1 && fm -> spaceplus)
	{
		*dest = fm -> spaceplus;
		return (1);
	}
	else if (sign == 2 && (fm -> alter || fm -> format_spec == 'p'))
	{
		if (fm -> format_spec == 'x' || fm -> format_spec == 'p')
			*dest = 'x';
		else if (fm -> format_spec == 'X')
			*dest = 'X';
		*(dest + 1) = '0';
		return (2);
	}
	else
		return (0);
}
