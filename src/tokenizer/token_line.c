/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:11:16 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/11 02:42:46 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	process_separator_type(char **line, t_token **token_lst)
{
	if (!ft_strncmp(*line, "<<", 2) || !ft_strncmp(*line, ">>", 2)
		|| !ft_strncmp(*line, "<", 1) || !ft_strncmp(*line, ">", 1))
		return (add_separator_token(REDIR, line, token_lst) && 1);
	else
		return (add_separator_token(PIPE, line, token_lst) && 1);
}

t_token	*tokenize_line(char *line)
{
	int		is_error;
	t_token	*token_lst;

	is_error = 0;
	token_lst = NULL;
	while (*line)
	{
		if (is_error)
			return (clear_list(&token_lst), NULL);
		if (is_space(*line))
			skip_spaces(&line);
		else if (!ft_strncmp(line, "|", 1) || !ft_strncmp(line, "<", 1)
		|| !ft_strncmp(line, ">", 1))
			is_error = (!process_separator_type(&line, &token_lst) && 1);
		else
			is_error = (!process_command(&line, &token_lst) && 1);
	}
	return (token_lst);
}
