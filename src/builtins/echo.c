/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:47 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/25 14:14:32 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Función para verificar si se debe omitir el salto de linea
bool	should_omit_newline(char **av)
{
	return (av[1] != NULL && ft_strcmp(av[1], "-n") == 0);
}

//Función para imprimir un argumento, manejando las comillas si es necesario
void	print_argument(char *arg)
{
	char	quote_char;
	size_t	len;

	if (arg[0] == '"' || arg[0] == '\'')
	{
		quote_char = arg[0];
		len = ft_strlen(arg);
		if (len > 0 && arg[len - 1] == quote_char)
		{
			arg[len - 1] = '\0';
			printf("%s", arg + 1);
		}
		else
			printf("%s", arg);
	}
	else
		printf("%s", arg);
}

void	our_echo(char **av)
{
	int		i;
	bool	no_newline;

	i = 1;
	no_newline = should_omit_newline(av);
	if (no_newline)
		i = 2;
	while (av[i] != NULL)
	{
		print_argument(av[i]);
		if (av[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	g_exit_status = 0;
}
