/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:35:15 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/07/24 21:42:40 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_printf.h"

static int	ft_digtoi(const char *nptr)
{
	int	res;

	res = 0;
	if (!nptr)
		return (0);
	while (ft_isdigit(*nptr))
	{
		res = (res * 10) + *nptr - 48;
		nptr++;
	}
	return (res);
}

t_fm	new_format(void)
{
	t_fm	new;

	new.format_spec = 0;
	new.width = 0;
	new.precision = -1;
	new.alter = 0;
	new.zerominus = 0;
	new.spaceplus = 0;
	return (new);
}

static void	get_format2(const char *ptr, t_fm *fm)
{
	fm -> width = ft_digtoi(ptr);
	while (ft_isdigit(*ptr))
		ptr++;
	if (*ptr == '.')
	{
		ptr++;
		if (fm -> zerominus == '0')
			fm -> zerominus = 0;
		fm -> precision = ft_digtoi(ptr);
		while (ft_isdigit(*ptr))
			ptr++;
	}
	if (ft_strchr("cspdiuxX%", *ptr))
		fm -> format_spec = *ptr;
	return ;
}

t_fm	get_format(const char *ptr)
{
	t_fm	fm;

	fm = new_format();
	while (ft_strchr("#0- +", *ptr))
	{
		if (*ptr == '#')
			fm.alter = 1;
		if (*ptr == '0' && fm.zerominus == 0)
			fm.zerominus = '0';
		if (*ptr == '-')
			fm.zerominus = '-';
		if (*ptr == ' ' && fm.spaceplus == 0)
			fm.spaceplus = ' ';
		if (*ptr == '+')
			fm.spaceplus = '+';
		ptr++;
	}
	get_format2(ptr, &fm);
	return (fm);
}
