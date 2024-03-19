/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:47 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/19 13:24:56 by irivero-         ###   ########.fr       */
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

/*void	our_echo(char **av)
{
	int		i;
	char	c;

	c = 'y';
	i = 1;
	if (echo_helper(av, &c, &i) == 1)
		return ;
	while (av[i] != NULL)
	{
		if (is_quoted(av[i]))
			print_without_quotes(av[i]);
		else
			b_putstr(av[i]);
		if (av[i + 1] != NULL)
			write(1, " ", 1);
		if (av[i + 1] == NULL && c == 'y' && av[i][0] != '\n')
			write(1, "\n", 1);
		i++;
	}
	g_exit_status = 0;
	//exit(g_exit_status);
	return ;
}*/
void our_echo(char **av) {
    int i = 1;
    int no_newline = 0;

    if (av[1] != NULL && strcmp(av[1], "-n") == 0) {
        no_newline = 1;
        i = 2;
    }

    while (av[i] != NULL) {
        // Ignorar las comillas simples y dobles al imprimir
        if (av[i][0] == '"' || av[i][0] == '\'') {
            char *str = av[i] + 1; // Saltar la comilla inicial
            int len = strlen(str);
            if (len > 0 && str[len - 1] == av[i][0]) {
                // Si la cadena termina con la misma comilla que al principio, eliminarla
                str[len - 1] = '\0';
                b_putstr(str);
            } else {
                // Si la cadena no termina con la misma comilla, imprimir como está
                b_putstr(av[i]);
            }
        } else {
            b_putstr(av[i]);
        }

        if (av[i + 1] != NULL) {
            write(1, " ", 1); // Agregar un espacio entre los argumentos
        }
        i++;
    }

    if (!no_newline) {
        write(1, "\n", 1); // Agregar una nueva línea al final si no se especifica la opción -n
    }

    g_exit_status = 0;
}
