/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:52:06 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/26 12:39:56 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_separator_token(int type, char **line, t_token **token_lst)
{
	t_token	*token;
	
	token = create_token(NULL, type);
	if (!token)
		return (0);
	token_lst_add_back(token_lst, token);
	(*line)++;
	if (type == DGREAT || type == DLESS)
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
			if(!skip_quotes(current_char, &i))
			{
				printf("Error: Missing closing quote.\n");
				return (0);
			}
		}
		else
			i++;
	}
	identifier = ft_substr(*line, 0, i);
	if (!identifier)
		return (0);
	token = create_token(identifier, WORD);
	if (!token)
		return (free(identifier), 0);
	*line = *line + i;
	return (token_lst_add_back(token_lst, token), 1);
}
