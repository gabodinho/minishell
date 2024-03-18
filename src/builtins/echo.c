/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:47 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/18 13:38:39 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

void	our_echo(char **av)
{
	int		i;
	char	c;

	c = 'y';
	i = 1;
	if (echo_helper(av, &c, &i) == 1)
		return ;
	while (av[i] != NULL)
	{
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
}