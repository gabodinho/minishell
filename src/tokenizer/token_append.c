/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:52:06 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/02 18:41:30 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	process_current_char(char **line, t_token *lst)
{
	if (*(*line + 1) == **line)
	{
		if (**line == '>')
			lst->str = ft_strdup(">>");
		else
			lst->str = ft_strdup("<<");
		(*line)++;
	}
	else
	{
		if (**line == '>')
			lst->str = ft_strdup(">");
		else
			lst->str = ft_strdup("<");
	}
}

int	add_separator_token(int type, char **line, t_token **token_lst)
{
	t_token	*token;

	token = create_token(NULL, type);
	if (!token)
		return (0);
	if (**line == '>' || **line == '<')
		process_current_char(line, token);
	else if (**line == '|')
		token->str = ft_strdup("|");
	token_lst_add_back(token_lst, token);
	(*line)++;
	return (1);
}

char	*get_command_identifier(char *line)
{
	size_t	i;
	char	*current_char;

	i = 0;
	current_char = line;
	while (current_char[i] && !is_shell_separator(current_char + i))
	{
		if (is_quotes(current_char[i]))
		{
			if (!skip_quotes(current_char, &i))
				return (NULL);
		}
		else if (is_space(current_char[i]))
			break ;
		else
			i++;
	}
	return (ft_substr(line, 0, i));
}

int	process_command(char **line, t_token **token_lst)
{
	t_token	*token;
	char	*identifier;

	identifier = get_command_identifier(*line);
	if (!identifier)
		return (0);
	token = create_token(identifier, WORD);
	free(identifier);
	if (!token)
		return (0);
	*line = *line + ft_strlen(token->str);
	return (token_lst_add_back(token_lst, token), 1);
}
/*
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
			if (!skip_quotes(current_char, &i))
				return (print_quotes_error(current_char[i]), 0);
		}
		else if (is_space(current_char[i]))
			break ;
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
}*/
