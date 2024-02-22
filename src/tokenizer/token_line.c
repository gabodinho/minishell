/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:11:16 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/22 17:28:05 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int process_separator_type(char **line)
{
	t_token	*token_lst;
	
	if (!ft_strncmp(*line, "<<", 2) || !ft_strncmp(*line, ">>", 2)
		|| !ft_strncmp(*line, "<", 1) || !ft_strncmp(*line, ">", 1))
		return (add_separator_token(REDIR, line, token_lst));
	else
		return (add_separator_token(PIPE, line, token_lst));
}

t_token *tokenize_line(char *line)
{
	int		is_error;
	t_token	*token;

	is_error = 0;
	token = NULL;
	while (line != NULL)
	{
		if (is_error)
			//return clear and return)
		if (is_space(line))
			skip_spaces(&line);
		else if (!ft_strncmp(line, "|", 1) || !ft_strncmp(line, "(", 1)
			|| !ft_strncmp(line, ")", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1))
			is_error = (!process_separator_type(&line) && 1);
		else
			//is_error = process_command()
	}
	return (token);
}