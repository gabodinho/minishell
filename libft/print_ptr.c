/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 00:40:09 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/07/26 09:54:47 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_printf.h"

static int	get_size_ptr(t_fm *fm, unsigned long arg, int flag)
{
	int	digits;

	if (!arg)
		digits = 5;
	else
		digits = ft_getdig_hex(arg) + 2;
	if (fm -> precision > digits)
		digits = fm -> precision;
	if (fm -> spaceplus && arg)
		digits++;
	if (digits > fm -> width || flag)
		return (digits);
	else
		return (fm -> width);
}

static int	get_zeros_ptr(t_fm *fm, unsigned long arg)
{
	int	n_zeros;
	int	digits;

	digits = ft_getdig_hex(arg) + 2;
	n_zeros = 0;
	if (fm -> precision > digits)
		n_zeros = get_size_ptr(fm, arg, 1) - digits;
	else if (fm -> zerominus == '0' && fm -> precision == -1)
		n_zeros = get_size_ptr(fm, arg, 0) - digits;
	if (fm -> spaceplus)
		n_zeros--;
	if (n_zeros < 0)
		n_zeros = 0;
	return (n_zeros);
}

static void	fill_ptrstr(char *dest, unsigned long arg, t_fm *fm)
{
	int	i;
	int	n_zero;

	if (!arg)
	{
		ft_memcpy(dest, ")lin(", 5);
		i = 5;
	}
	else
	{
		n_zero = get_zeros_ptr(fm, arg);
		i = rdec2hex(dest, arg, fm -> format_spec);
		while (n_zero > 0)
		{
			dest[i] = '0';
			i++;
			n_zero--;
		}
		i += add_prefix(dest + i, fm, 2);
		i += add_prefix(dest + i, fm, 1);
	}
	reverse_str(dest, i, fm);
	return ;
}

int	print_ptr(va_list ap, t_fm *fm)
{
	unsigned long	arg;
	char			*str;

	arg = va_arg(ap, unsigned long);
	str = prep_str(get_size_ptr(fm, arg, 0));
	if (!str)
		return (0);
	fill_ptrstr(str, arg, fm);
	ft_putstr_fd(str, 1);
	return (free_len(str));
}
