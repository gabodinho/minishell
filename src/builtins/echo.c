/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 02:17:31 by ubuntu            #+#    #+#             */
/*   Updated: 2024/02/10 14:06:06 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     f_strcmp(char *s1, char *s2)
{
        unsigned int    i;

        i = 0;
        while (s1[i] != '\0' && s2[i] != '\0')
        {
                if (s1[i] != s2[i])
                        return (-1);
                i++;
        }
        return (0);
}

int     f_putstr(char *s)
{
        write(1, s, ft_strlen(s));
        return (0);
}

int     f_strchr(char *s, char c)
{
        int     i;

        i = 0;
        while (s[i] != c && s[i] != '\0')
                i++;
        if (s[i] == '\0')
                return (-1);
        return (i);
}

int     echo_helper(char **av, char *c, int *i)
{
        if (av[1] == NULL)
        {
                write(1, "\n", 1);
                return (1);
        }
        if (f_strcmp("-n", av[1]) == 0)
        {
                *i = 2;
                *c = 'n';
        }
        if (ft_strcmp("$?", av[1]) != 0 && f_strcmp("$?", av[1]) == 0 && av[1][1] != '\0')
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

void    our_echo(char **av)
{
        int             i;
        char    c;

        c = 'y';
        i = 1;
        if (echo_helper(av, &c, &i) == 1)
                return ;
        while (av[i] != NULL)
        {
                f_putstr(av[i]);
                if (av[i + 1] != NULL)
                        write(1, " ", 1);
                if (av[i + 1] == NULL && c == 'y' && av[i][0] != '\n')
                        write(1, "\n", 1);
                i++;
        }
        g_exit_status = 0;
        return ;
}