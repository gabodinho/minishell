/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:52:06 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/22 17:49:08 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_separator_token(int type, const char **line, t_token **token_lst)
{
	t_token	*token;
	
	token = create_token(NULL, type);
	if (!token)
		return (0);
	token_lst_add_back(token_lst, token);
	(*line)++;
	if (type == REDIR)
		(*line)++;
	return (1);
}

int	process_command(char **line, t_token **token_lst)
{
	t_token	*token;
	char	*identifier;
	size_t	i;
	char	*current_char;

	i = 0;
	current_char = *line;
	while (current_char[i] && !is_shell_separator(current_char + i))
	{
		if (is_quotes(current_char[i]))
		{
			
		}
		i++;
	}
}