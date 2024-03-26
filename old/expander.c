/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:57:15 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/14 17:00:58 by irivero-         ###   ########.fr       */
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
	while (env[i] != NULL) 
	{
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

char	*string_quotes(char *str)
{
	int	i;
	char	*new_str;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (new_str == NULL)
		return (NULL);
	while (str[i + 1] != '\0')
	{
		new_str[i] = str[i + 1];
		i++;
	}
	new_str[i - 1] = '\0';
	//free(str);
	return (new_str);
}

void	single_quote_(char **cmd, int i)
{
	cmd[i] = string_quotes(cmd[i]);
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
			else if (cmd[i][0] == '\'')
				single_quote_(cmd, i);
		}
		i++;
	}
	//expand_single_quotes(cmd);
	//expand_quotes(cmd, env);
	return (0);
}
/*
void	expand_single_quotes(char **cmd)
{
	int		i;
	int		d;
	int		end;
	char	*var;
	char	*quoted_var;
	char	*var_value;

	i = 0;
	while (cmd[i] != NULL)
	{
		d = -1;
		while (cmd[i][++d] != '\0')
		{
			if (cmd[i][d] == '\'' && cmd [i][d + 1] == '$')
			{
				end = strchr(cmd[i] + d + 1, '\'') - (cmd[i] + d + 1);
				if (end != 1)
				{
					var = ft_substr(cmd[i], d + 2, end);
					if (var)
					{
						quoted_var = ft_strjoin("'", var);
						cmd[i] = str_modifier(cmd[i], quoted_var, d);
						if (cmd[i] == NULL)
							return;
					}
					free(quoted_var);
					free(var);
				}
			}
		}
		i++;
	}
}

void	expand_quotes(char **cmd, char **env)
{
	int		i;
	int		d;
	int		end;
	char	*var;
	int		v;
	char	*var_value;

	i = 0;
	while (cmd[i] != NULL)
	{
		d = -1;
		while (cmd[i][d] == '\"' && cmd [i][d + 1] == '$')
		{
			end = strchr(cmd[i] + d + 1, '\"') - (cmd[i] + d + 1);
			if (end != 1)
			{
				var = ft_substr(cmd[i], d + 2, end);
				if (var)
				{
					v = var_finder(env, var);
					if (v != -1)
					{
						var_value = strchr(env[v], '=') + 1;
						cmd[i] = str_modifier(cmd[i], var_value, d);
						if (cmd[i] == NULL)
							return;
					}
					free(var);
					//expansion(&cmd[i], env);
				}
			}
		}
		i++;
	}
}
*/
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
