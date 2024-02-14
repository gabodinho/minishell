/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:58:15 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/14 17:17:40 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// need function to count the tokens and also to find the end of the tokens
// maybe find the tokens and put them in an array with individual token strings
// take into account the quotes and spaces
// function to iterate through the characters of the line

void	count_tokens(char *str, int *i, int *size)
{
	int		quote;

	while (is_space(str[*i]))
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = quotes_end(str, *i, NULL);
		if (quote != -1)
		{
			*i = quote + 1;
			(*size)++;
		}
	}
	else
	{
		while (str[*i] != '\0' && !is_space(str[*i]) && str[*i] != '\''
			&& str[*i] != '\"')
			(*i)++;
		(*size)++;
	}
}

int	counter_simplified(char *str)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		count_tokens(str, &i, &size);
		if (i == -1)
			return (-1);
	}
	return (size);
}


int main()
{
    char *str = "This 'is a' test \"string\" for the tokenizer function.";
    int i = 0;
    int size = 0;
    while (str[i] != '\0')
        count_tokens(str, &i, &size);
	printf("string: %s\n", str);
    printf("size with the first function: %d\n", size);
	while (str[i] != '\0')
		counter_simplified(str);
	printf("counter function: %d\n", size);
    return (0);
}