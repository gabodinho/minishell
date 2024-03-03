/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 00:11:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/07/24 22:43:33 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

static int	get_size_str(t_fm *fm, const char *arg, int flag)
{
	int	len;

	len = ft_strlen(arg);
	if (fm -> precision < len && fm -> precision != -1)
		len = fm -> precision;
	if (len > fm -> width || flag)
		return (len);
	else
		return (fm -> width);
}

static char	*fill_strstr(const char *arg, t_fm *fm)
{
	int		prt_len;
	int		buf_len;
	char	*str;

	buf_len = get_size_str(fm, arg, 0);
	prt_len = get_size_str(fm, arg, 1);
	str = prep_str(buf_len);
	if (!str)
		return (0);
	if (fm -> zerominus == '-')
		ft_memcpy(str, arg, prt_len);
	else
		ft_memcpy(str + (buf_len - prt_len), arg, prt_len);
	return (str);
}

int	print_str(va_list ap, t_fm *fm)
{
	const char	*arg;
	char		*str;

	arg = va_arg(ap, const char *);
	if (!arg)
	{
		if (fm -> precision < 6 && fm -> precision != -1)
		{
			fm -> precision = 0;
			arg = "";
		}
		else
			arg = "(null)";
	}
	str = fill_strstr(arg, fm);
	ft_putstr_fd(str, 1);
	return (free_len(str));
}

int	print_char(va_list ap, t_fm *fm)
{
	unsigned char	arg;
	char			*str;
	int				ret;

	arg = (unsigned char) va_arg(ap, int);
	if (fm -> width == 0)
		fm -> width = 1;
	str = prep_str(fm -> width);
	if (!str)
		return (0);
	if (fm -> zerominus == '-')
		*str = arg;
	else
		str[fm -> width - 1] = arg;
	write(1, str, fm -> width);
	ret = fm -> width;
	free(str);
	return (ret);
}
