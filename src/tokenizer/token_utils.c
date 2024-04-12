/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:14:22 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/02 13:48:49 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

//check if a character is a space
int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

void	skip_spaces(char **str)
{
	while (**str && is_space(**str))
		(*str)++;
}

int	is_shell_separator(char *c)
{
	if (*c == '|' || *c == '<' || *c == '>' || *c == '\t')
		return (1);
	return (0);
}

int	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}
