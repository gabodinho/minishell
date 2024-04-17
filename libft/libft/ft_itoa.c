/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:14:13 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/16 15:09:07 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	get_abs(long int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

int	get_len(long int nbr)
{
	int		len;

	if (nbr <= 0)
		len = 1;
	else
		len = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	if (n < 0)
		sign = -1;
	else
		sign = 1;
	len = get_len(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (0);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = '0' + get_abs(n % 10);
		n = get_abs(n / 10);
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
