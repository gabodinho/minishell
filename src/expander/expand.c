/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:39:49 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/11 02:36:13 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "expander.h"

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
	char	*env_entry;

	current = env;
	while (current)
	{
		env_entry = (char *)(current->content);
		if (ft_strncmp(env_entry, env_key, ft_strlen(env_key)) == 0
			&& env_entry[ft_strlen(env_key)] == '=')
		{
			result = ft_strdup(env_entry + ft_strlen(env_key) + 1);
			if (result == NULL)
				return (NULL);
			return (result);
		}
		current = current->next;
	}
	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	return (result);
}

char	*create_string(t_string_info *info, char *token, int start_d, int end_d)
{
	char	*value;
	char	*key;
	char	*new_str;
	int		len;

	key = ft_substr(token, start_d + 1, end_d - start_d);
	if (ft_strncmp(key, "?", ft_strlen(key)) == 0)
		value = ft_itoa(info->exit_status);
	else
		value = get_env_value(info->env, key);
	len = ft_strlen(token) - (end_d - start_d + 1) + ft_strlen(value);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	new_string(new_str, ft_substr(token, 0, start_d), value,
		ft_substr(token, end_d + 1, ft_strlen(token)));
	free(key);
	free(value);
	return (new_str);
}
