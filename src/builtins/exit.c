/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 02:17:45 by ubuntu            #+#    #+#             */
/*   Updated: 2024/02/09 02:17:48 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     av_counter(char **av)
{
        int     i;

        i = 0;
        while (av[i])
                i++;
        return (i);
}

void    if_i_is_two(char **av)
{
        if (ft_isdigit(av[1][0]) == 0)
        {
                printf("exit: %s: numeric argument required\n", av[1]);
                g_exit_status = 2;
        }
        else
        {
                g_exit_status = ft_atoi(av[1]);
                exit(g_exit_status);
        }
}

void    exit_command(char **av)
{
        int             i;

        i = av_counter(av);
        if (i > 2)
        {
                printf("exit: too many arguments\n");
                g_exit_status = 1;
        }
        else if (i == 1)
        {
                g_exit_status = 0;
                exit(g_exit_status);
        }
        else if (i == 2)
                if_i_is_two(av);
        exit (g_exit_status);
}