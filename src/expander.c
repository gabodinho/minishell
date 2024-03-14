/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:57:15 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/14 11:43:56 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/expander.h"
#include "../libft/libft/libft.h"
#include <stddef.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h>

int	var_finder(char **env, const char *s) 
{
	int i = 0;
	if (s == NULL || *s == '\0')
		return (-1);
	while (env[i] != NULL) {
		if (strstr(env[i], s) == env[i])
			return (i); 
		i++;
	}
	return (-1);
}

char	*str_modifier(const char *str, const char *var_value, int d) 
{
	size_t var_value_len = ft_strlen(var_value);
	size_t str_len = ft_strlen(str);
	size_t new_str_len = str_len - 2 + var_value_len;
	
	char *new_str = (char *)malloc((new_str_len + 1) * sizeof(char));
	if (new_str == NULL)
		return NULL;
	// Copia la parte inicial de la cadena antes de la variable
	ft_memcpy(new_str, str, d);
	// Copia el valor de la variable
	strcpy(new_str + d, var_value);
	// Copia la parte restante de la cadena después de la variable
	//strcpy(new_str + d + var_value_len, str + d + 2); // Salta el símbolo '$' y el espacio adicional
	return (new_str);
}

int	expansion(char **cmd, char **env) 
{
	int i = 0;
	while (cmd[i] != NULL) 
	{
		int d = -1;
		while (cmd[i][++d] != '\0') 
		{
			if (cmd[i][d] == '$' && cmd[i][d + 1] != '\0') 
			{
				int v = var_finder(env, cmd[i] + d + 1);
				if (v != -1) 
				{
					char *var_value = strchr(env[v], '=') + 1;
					cmd[i] = str_modifier(cmd[i], var_value, d);
					if (cmd[i] == NULL)
						return (-1); 
				}
			}
		}
		i++;
	}
	return (0);
}

int main(void) 
{
	char *env[] = {"HOME=/home/user", "PATH=/usr/bin", "USER=user", NULL};
	char *cmd[] = {"echo", "$HOME", "is", "my", "home", "directory", NULL};

	expansion(cmd, env);

	int i = 0;
	while (cmd[i] != NULL) 
	{
		printf("%s ", cmd[i]);
		i++;
	}
	printf("\n");

	return 0;
}
