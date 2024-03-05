/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:52:06 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/27 12:33:35 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_separator_token(int type, char **line, t_token **token_lst)
{
	t_token	*token;
	
	token = create_token(NULL, type);
	if (!token)
		return (0);
		/*
	if (type == PIPE)
		token->str = ft_strdup("|");
	else if (type == DLESS)
		token->str = ft_strdup("<<");
	else if (type == DGREAT)
		token->str = ft_strdup(">>");
	else if (type == LESS)
		token->str = ft_strdup("<");
	else if (type == GREAT)
		token->str = ft_strdup(">");
	*/

	if (**line == '>' || **line == '<')
	{
		if (*(*line + 1) == **line)
		{
			if (**line == '>')
				token->str = ft_strdup(">>");
			else
				token->str = ft_strdup("<<");
			(*line)++;
		}
		else
		{
			if (**line == '>')
				token->str = ft_strdup(">");
			else
				token->str = ft_strdup("<");
		}
	}
	else if (**line == '|')
		token->str = ft_strdup("|");
	token_lst_add_back(token_lst, token);
	(*line)++;
	//if (type == DGREAT || type == DLESS)
	//	(*line)++;
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
		else if (is_space(current_char[i]))
			break;
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
