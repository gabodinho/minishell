/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:14:22 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/27 12:46:14 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

//skip spaces 
void	skip_spaces(char **str)
{
	while (**str && is_space(**str))
		(*str)++;
}

int	is_shell_separator(char *c)
{
	if (*c == '|' || *c == '(' || *c == ')' || *c == '<' || *c == '>' || *c == '\t'
		|| !ft_strncmp(c, "&&", 2))
		return (1);
	return (0);
}

int	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

bool	skip_quotes(char *line, size_t  *i)
{
	char	quote;
	char	*end_quote;

	quote = line[*i];
	end_quote = ft_strchr(line + *i + 1, quote);
	if (end_quote != NULL)
	{
		//(*i) += 1 + (end_quote - (line + *i + 1));
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}
/*temporal hasta acceso a libft
char	*ft_substr(const char *str, int start, int length)
{
	if (str == NULL || start < 0 || length < 0)
    	return NULL;
    int str_len = 0;
    while (str[str_len] != '\0')
        str_len++;
    if (start >= str_len)
        return NULL;
    int sub_len = (length == 0) ? str_len - start : length;
    char *substring = (char *)malloc((sub_len + 1) * sizeof(char));
    if (substring == NULL)
        return NULL;
    const char *src = str + start;
    char *dest = substring;
    while (*src != '\0' && sub_len-- > 0)
        *dest++ = *src++;
    *dest = '\0';
    return (substring);
}
*/