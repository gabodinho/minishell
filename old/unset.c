/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:51:55 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/12 10:12:54 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	b_strcmpt(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i ++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

int	last_variable(char **env)
{
	int	i;

	i = 0;
	while (env[i + 1] != NULL)
		i++;
	return (i);
}

void	ft_unset(char *v_name, t_envp *env)
{
	int	i;
	int	lv;

	i = 0;
	printf("calling ft_unset\n");
	while (env->envp[i] != NULL)
	{
		if (b_strcmpt(v_name, env->envp[i]) == 0)
		{
			if (env->envp[i + 1] == NULL)
			{
				env->envp[i] = NULL;
				return ;
			}
			else
			{
				lv = last_variable(env->envp);
				env->envp[i] = env->envp[lv];
				env->envp[lv] = NULL;
				return ;
			}
		}
		i++;
	}
	return ;
}