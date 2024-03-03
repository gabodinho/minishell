/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 00:40:09 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/01 16:01:19 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_printf.h"

static int	put_ruint(long arg, char *dest, t_fm *fm)
{
	int	i;

	i = 0;
	if (!arg && !fm -> precision)
		return (0);
	else if (arg == 0)
	{
		dest[0] = '0';
		return (1);
	}
	else if (arg < 0)
		arg *= -1;
	while (arg)
	{
		dest[i] = arg % 10 + 48;
		arg = arg / 10;
		i++;
	}
	return (i);
}

static int	get_zeros(t_fm *fm, long arg)
{
	int	n_zeros;
	int	digits;

	digits = ft_getdig(arg, 10);
	n_zeros = 0;
	if (!arg && !fm -> precision)
		return (0);
	if (fm -> precision >= digits)
	{
		n_zeros = fm -> precision - digits;
		if (arg < 0)
			n_zeros++;
	}
	else if (fm -> width > digits && fm -> zerominus == '0')
	{
		n_zeros = fm -> width - digits;
		if (fm -> spaceplus && arg >= 0 && fm -> precision == -1)
			n_zeros--;
	}
	return (n_zeros);
}

void	fill_decstr(char *dest, long arg, t_fm *fm)
{
	int	i;
	int	sign;
	int	n_zero;

	n_zero = get_zeros(fm, arg);
	sign = 1;
	if (arg < 0)
		sign = -1;
	i = put_ruint(arg, dest, fm);
	while (n_zero > 0)
	{
		dest[i] = '0';
		i++;
		n_zero--;
	}
	i += add_prefix(dest + i, fm, sign);
	reverse_str(dest, i, fm);
	return ;
}

int	print_dec(va_list ap, t_fm *fm)
{
	long	arg;
	char	*str;

	arg = va_arg(ap, int);
	str = prep_str(get_size_dec(fm, arg, 0));
	if (!str)
		return (0);
	fill_decstr(str, arg, fm);
	ft_putstr_fd(str, 1);
	return (free_len(str));
}

int	print_u(va_list ap, t_fm *fm)
{
	unsigned int	arg;
	char			*str;

	arg = va_arg(ap, unsigned int);
	fm -> spaceplus = 0;
	str = prep_str(get_size_dec(fm, arg, 0));
	if (!str)
		return (0);
	fill_decstr(str, arg, fm);
	ft_putstr_fd(str, 1);
	return (free_len(str));
}
