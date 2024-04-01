/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:39:49 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/30 08:55:33 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "expander.h"

int	is_envirom(char *str, int i)
{
	if (str[i] == '$')
	{
		if (str[i + 1] == '$')
			return (0);
		if (str[i + 1] == '\0')
			return (0);
		if (ft_isalpha(str[i + 1]))
			return (1);
		if (str[i + 1] == '?')
			return (1);
		if (str[i + 1] == '-')
			return (1);
	}
	return (0);
}

int	is_env_char(char c)
{
	if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
		return (1);
	else
		return (0);
}

int	is_token_in_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_envirom(str, i))
			return (i);
		i++;
	}
	return (-1);
}

int	find_dollar(char *str, int i)
{
	if (str[i] == '?')
		return (i);
	while (is_env_char(str[i]))
		i++;
	return (i - 1);
}

void	new_string(char *new_str, char *subs1, char *value, char *subs2)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = subs1;
	tmp2 = subs2;
	while (*subs1 != '\0')
		*(new_str++) = *(subs1++);
	while (*value != '\0')
		*(new_str++) = *(value++);
	while (*subs2 != '\0')
		*(new_str++) = *(subs2++);
	*new_str = '\0';
	free(tmp1);
	free(tmp2);
}
char	*get_env_value(t_list *env, char *env_key)
{
	char	*result;
	t_list	*current;

	current = env;
	while (current)
	{
		char *env_entry = (char *)(current->content);
		if (ft_strncmp(env_entry, env_key, ft_strlen(env_key)) == 0 && env_entry[ft_strlen(env_key)] == '=')
		{
			// Si encontramos la variable de entorno, devolvemos el valor
			result = ft_strdup(env_entry + ft_strlen(env_key) + 1); // Apuntamos al inicio del valor (después del igual)
			if (result == NULL)
				return (NULL);
			return (result);
		}
		current = current->next;
	}
	// Si no se encuentra la variable de entorno, devolvemos una cadena vacía
	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	return (result);
}

char	*create_string(t_list *env, char *token, int start_d, int end_d, int exit_status)
{
	char	*value;
	char	*key;
	char	*new_str;
	int		len;

	key = ft_substr(token, start_d + 1, end_d - start_d);
	if (ft_strncmp(key, "?", ft_strlen(key)) == 0)
		value = ft_itoa(exit_status);
	else
		value = get_env_value(env, key);
	len = ft_strlen(token) - (end_d - start_d + 1) + ft_strlen(value);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	new_string(new_str, ft_substr(token, 0, start_d), value, ft_substr(token, end_d + 1, ft_strlen(token)));
	free(key);
	free(value);
	return (new_str);
}

void	expander(t_list *env, t_token *token, int exit_status)
{
	t_token		*current;
	int			start_d;
	int			end_d;
	char		*new_str;
	//int			single_quotes;
	//t_token		*prev;

	current = token;
	while (current)
	{
		if (current->str[0] != '\'')
		{
			start_d = is_token_in_env(current->str);
			if (start_d != -1)
			{
				//single_quotes = 0;
				//prev = current->prev;
				//while (prev && prev->type != '\n')
				//{
				//	if (prev->type == '\'')
				//		single_quotes = !single_quotes;
				//	prev = prev->prev;
				//}
				//if (!single_quotes)
				//{
				end_d = find_dollar(current->str, start_d + 1);
				new_str = create_string(env, current->str, start_d, end_d, exit_status);
				free(current->str);
				current->str = new_str;
				//}
			}
		}
		current = current->next;
	}
}
