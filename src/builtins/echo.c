/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:47 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/04 15:33:42 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Función para verificar si se debe omitir el salto de linea
int	should_omit_newline(char *av)
{
	int	i;

	i = 0;
	if (av[0] != '-')
		return (0);
	i++;
	while (av[i])
	{
		if (av[i] == 'n')
			return (1);
		i++;
	}
	return (1);
}

int	our_echo(char **av)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	while (av[i] != NULL && should_omit_newline(av[i]) == 1)
	{
		no_newline = 1;
		i++;
	}
	while (av[i] != NULL)
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (no_newline == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
