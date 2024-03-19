/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:47 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/19 16:08:14 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	is_quoted(const char *str)
{
	int	len;

	len = ft_strlen(str);
	return ((len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		|| (len >= 2 && str[0] == '"' && str[len - 1] == '"'));
}

void	print_without_quotes(const char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 1;
	while (i < len - 1)
	{
		printf("%c", str[i]);
		i++;
	}
}

int	echo_helper(char **av, char *c, int *i)
{
	if (av[1] == NULL)
	{
		write(1, "\n", 1);
		return (1);
	}
	if (b_strcmp("-n", av[1]) == 0)
	{
		*i = 2;
		*c = 'n';
	}
	if (ft_strcmp("$?", av[1]) != 0 && b_strcmp("$?", av[1]) == 0 && av[1][1] != '\0')
	{
		printf("no matches found: 0?\n");
		g_exit_status = 1;
		return (1);
	}
	else if (ft_strcmp("$?", av[1]) == 0)
	{
		printf("%i\n", g_exit_status);
		return (1);
	}
	return (0);
}

void our_echo(char **av) 
{
	int 	i;
	bool	no_newline;
	char	quote_char;
	char	*str;
	size_t 	len;

	i = 1;
	no_newline = false;
	// Verificar si se especificó la opción -n
	if (av[1] != NULL && strcmp(av[1], "-n") == 0) 
	{
		no_newline = true;
		i = 2;
	}

	// Recorrer los argumentos
	while (av[i] != NULL) 
	{
		// Verificar si el argumento está entre comillas simples o dobles
		if (av[i][0] == '"' || av[i][0] == '\'') 
		{
			quote_char = av[i][0];
			str = av[i] + 1;  // Apuntar al primer carácter después de la comilla inicial
			len = strlen(str);
			// Verificar si el argumento termina con la misma comilla que al principio
			if (len > 0 && str[len - 1] == quote_char) 
			{
				// Si termina con la misma comilla, eliminarla y imprimir el contenido
				str[len - 1] = '\0';
				printf("%s", str);
			} 
			else
				// Si no termina con la misma comilla, imprimir el argumento como está
				printf("%s", av[i]);
		} 
		else
			// Si el argumento no está entre comillas, imprimirlo como está
			printf("%s", av[i]);
		// Agregar un espacio entre los argumentos si no es el último
		if (av[i + 1] != NULL)
			printf(" ");
		i++;
	}
	// Imprimir una nueva línea si no se especificó la opción -n
	if (!no_newline) 
		printf("\n");
	g_exit_status = 0;
}
