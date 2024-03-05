/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:51:58 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/07/24 21:43:01 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

static int	put_char(char arg, int fd)
{
	write(fd, &arg, 1);
	return (1);
}

static const char	*check_syntax(const char *ptr)
{
	while (ft_strchr("#0+- ", *ptr))
		ptr++;
	while (ft_isdigit(*ptr))
		ptr++;
	if (*ptr == '.')
	{
		ptr++;
		while (ft_isdigit(*ptr))
			ptr++;
	}
	if (ft_strchr("cspdiuxX%", *ptr))
		return (ptr);
	else
		return (0);
}

static int	print_arg(va_list ap, t_fm fm)
{
	if (ft_strchr("di", fm.format_spec))
		return (print_dec(ap, &fm));
	if (fm.format_spec == 'u')
		return (print_u(ap, &fm));
	if (fm.format_spec == 'c')
		return (print_char(ap, &fm));
	if (fm.format_spec == 's')
		return (print_str(ap, &fm));
	if (ft_strchr("xX", fm.format_spec))
		return (print_hex(ap, &fm));
	if (fm.format_spec == 'p')
		return (print_ptr(ap, &fm));
	if (fm.format_spec == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	int		res;
	va_list	ap;

	res = 0;
	va_start(ap, str);
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (check_syntax(str))
			{
				res += print_arg(ap, get_format(str));
				str = check_syntax(str);
			}
		}
		else
			res += put_char(*str, 1);
		str++;
	}
	va_end(ap);
	return (res);
}
