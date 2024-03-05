/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:26:20 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/05/23 17:21:25 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digtoi(const char *nptr)
{
	int	res;

	res = 0;
	while (ft_isdigit(*nptr))
	{
		res = (res * 10) + *nptr - 48;
		nptr++;
	}
	return (res);
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while ((*nptr >= '\011' && *nptr <= '\015') || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		res = ft_digtoi(nptr + 1);
	}
	else if (*nptr == '+')
		res = ft_digtoi(nptr + 1);
	else if (ft_isdigit(*nptr))
		res = ft_digtoi(nptr);
	return (res * sign);
}
/*
int main()
{
	char input[] = "\007 8";
    printf("Result atoi: %d\n", atoi(input));
	printf("Result ft_atoi: %d", ft_atoi(input));
    return (0);
}
*/
