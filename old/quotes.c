/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:53:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/19 13:02:03 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	handle_single_quotes(char **line)
{
	char	*ptr;

	ptr = *line;
	while (*ptr)
	{
		if (*ptr == '\'')
		{
			ptr**;
			while (*ptr && *ptr != '\'')
				ptr++;
		}
		ptr++;
	}
}

void	handle_double_quotes(char **line)
{
	char	*ptr;
	bool	inside_quotes;

	ptr = *line;
	while (*ptr)
	{
		if (*ptr == '"')
		{
			inside_quotes = true;
			ptr**;
			while (*ptr && inside_quotes)
			{
				if (*ptr == '$')
				{
				//	EXPANSION
				}
				else if (*ptr == '"')
					inside_quotes = false;
				ptr++;
			}
		}
		ptr++;
	}
}