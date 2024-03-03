/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:44:13 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/07/25 14:09:08 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <bsd/string.h>
# include <stdarg.h>
# include <stdint.h>
# include "./libft/libft.h"

typedef struct s_fm
{
	char	format_spec;
	int		width;
	int		precision;
	int		alter;
	char	zerominus;
	char	spaceplus;
}	t_fm;

size_t		ft_getdig(long long n, int base);		// change this
size_t		ft_getdig_hex(unsigned long n);
int			get_size_dec(t_fm *fm, long arg, char flag);
int			add_prefix(char *dest, t_fm *fm, int sign);
void		reverse_str(char *dest, int size, t_fm *fm);
t_fm		new_format(void);
t_fm		get_format(const char *ptr);
const char	*shift_ptr(const char *ptr);
char		*prep_str(size_t size);
int			free_len(char *str);
void		fill_decstr(char *dest, long arg, t_fm *fm);
long		rdec2hex(char *dest, unsigned long arg, char flag);
int			print_char(va_list ap, t_fm *fm);
int			print_dec(va_list ap, t_fm *fm);
int			print_str(va_list ap, t_fm *fm);
int			print_ptr(va_list ap, t_fm *fm);
int			print_dec(va_list ap, t_fm *fm);
int			print_u(va_list ap, t_fm *fm);
int			print_hex(va_list ap, t_fm *fm);
int			ft_printf(const char *str, ...);

#endif
