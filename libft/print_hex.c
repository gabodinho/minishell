/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 00:40:09 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/07/26 09:51:10 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_printf.h"

static int	get_size_hex(t_fm *fm, long arg, int flag)
{
	int	digits;

	digits = ft_getdig(arg, 16);
	if (fm -> precision > digits)
		digits = fm -> precision;
	if (fm -> alter)
		digits += 2;
	if (!arg && !fm -> precision)
		digits = 0;
	if (digits > fm -> width || flag)
		return (digits);
	else
		return (fm -> width);
}

static int	get_zeros_hex(t_fm *fm, long arg)
{
	int	n_zeros;
	int	digits;

	digits = ft_getdig(arg, 16);
	n_zeros = 0;
	if (fm -> precision > digits)
		n_zeros = get_size_hex(fm, arg, '1') - digits;
	else if (fm -> zerominus == '0' && fm -> precision == -1)
		n_zeros = get_size_hex(fm, arg, 0) - digits;
	if (fm -> alter)
		n_zeros -= 2;
	if (n_zeros < 0)
		n_zeros = 0;
	return (n_zeros);
}

static void	fill_hexstr(char *dest, long arg, t_fm *fm)
{
	int	i;
	int	n_zero;

	i = 0;
	n_zero = get_zeros_hex(fm, arg);
	if (arg || fm -> precision)
		i = rdec2hex(dest, arg, fm -> format_spec);
	while (n_zero > 0)
	{
		dest[i] = '0';
		i++;
		n_zero--;
	}
	i += add_prefix(dest + i, fm, 2);
	reverse_str(dest, i, fm);
	return ;
}

int	print_hex(va_list ap, t_fm *fm)
{
	unsigned int	arg;
	char			*str;

	arg = va_arg(ap, unsigned int);
	if (!arg)
		fm -> alter = 0;
	str = prep_str(get_size_hex(fm, arg, 0));
	if (!str)
		return (0);
	fill_hexstr(str, arg, fm);
	ft_putstr_fd(str, 1);
	return (free_len(str));
}
