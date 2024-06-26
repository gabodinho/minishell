/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:47 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/16 12:41:25 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Función para verificar si se debe omitir el salto de linea
int	should_omit_newline(const char *av)
{
	int	i;

	if (!av)
		return (0);
	if (av[0] != '-' || av[1] != 'n')
		return (0);
	i = 1;
	while (av[i])
	{
		if (av[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	our_echo(char **av)
{
	int	i;
	int	new;

	i = 1;
	new = 0;
	while (av[i])
	{
		if (should_omit_newline(av[i]) == 0 || new == 1)
		{
			new = 1;
			ft_putstr_fd(av[i], 1);
			if (av[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		i++;
	}
	if (should_omit_newline(av[1]) == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
