/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:41 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/11 09:31:25 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../libft/libft/libft.h"

int	ft_putstr(char *s)
{
	write(1, s, b_strlen(s));
	write(1, "\n", 1);
	return (0);
}

void	ft_env(t_envp *env)
{
	int	i = 0;
	while (env->envp[i] != NULL)
	{
		if (ft_putstr(env->envp[i]) == -1)
			return ;
		i++;
	}
	return ;
}
