/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:12 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/12 10:24:56 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	exporter(char *v_name, char *v_value, t_envp *env)
{
	int	i;
	int	k;
	int	m;

	i = 0;
	k = -1;
	m = 0;
	while (env->envp[i] != NULL)
		i++;
	env->envp[i] = malloc(b_strlen(v_name) + b_strlen(v_value) + 2);
	/*while (v_name[++k] != '\0')
		env->envp[i][k] = v_name[k];
	env->envp[i][k] = '=';
	k++;
	while (v_value[m] != '\0')
	{
		env->envp[i][k] = v_value[m];
		k++;
		m++;
	}
	env->envp[i][k] = '\0';
	i++;
	env->envp[i] = NULL;*/
	strcpy(env->envp[i], v_name);
	strcat(env->envp[i], "=");
	strcat(env->envp[i], v_value);
	env->envp[i + 1] = NULL;
	return (0);
}

void	export(char **builtin, t_envp *env)
{
	char	*v_name;
	char	*v_value;

	v_name = builtin[0];
	v_value = builtin[2];
	printf("calling export\n");
	printf("Before export:\n");
	for (int i =0; env->envp[i] != NULL; i++)
		printf("%s\n", env->envp[i]);
	if (v_value == NULL)
		v_value = "";
	if (*v_name == '=' || v_name == NULL)
	{
		printf("export: not an identifier: %s\n", v_name);
		g_exit_status = 1;
		return ;
	}
	if (var_finder(env->envp, v_name) != -1)
		ft_unset(v_name, env);
	if (exporter(v_name, v_value, env) != 0)
	{
		g_exit_status = 1;
		return ;
	}
	printf("After export:\n");
	for (int i =0; env->envp[i] != NULL; i++)
		printf("%s\n", env->envp[i]);
	g_exit_status = 0;
	return ;
}