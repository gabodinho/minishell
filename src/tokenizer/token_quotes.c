/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:48:23 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/02 13:48:51 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	skip_quotes(char *line, size_t *i)
{
	char	quote;
	char	*end_quote;

	quote = line[*i];
	end_quote = ft_strchr(line + *i + 1, quote);
	if (end_quote != NULL)
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		return (true);
	}
	return (false);
}

int	print_quotes_error(char c)
{
	ft_putstr_fd("minishell: unexpected EOF reached while looking for '", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("'", 2);
	return (258);
}
