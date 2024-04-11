/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:47 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/11 22:08:15 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Función para verificar si se debe omitir el salto de linea
int	should_omit_newline(const char *av)
{
	return (av[0] == '-' && av[1] == 'n' && av[2] == '\0');
}

int	our_echo(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!should_omit_newline(av[i]))
		{
			ft_putstr_fd(av[i], 1);
			if (av[i + 1])
				ft_putstr_fd(" ", 1);
		}
		i++;
	}
	if (!av[1] || !should_omit_newline(av[1]))
		ft_putstr_fd("\n", 1);
	return (0);
}
