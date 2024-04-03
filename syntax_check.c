/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 23:29:33 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/12 03:06:35 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	panic(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static int	synt_err(t_token	*prev, t_token *current)
{
	char	*culprit;

	culprit = NULL;
	if (!prev && current -> type == PIPE)
		culprit = "|";
	else if (!current && prev -> type == REDIR)
		culprit = "newline";
	else if (!current && prev -> type != REDIR)
		return (0);
	else if (prev && prev -> type == REDIR && current -> type == REDIR)
		culprit = current -> str;
	else if (prev && prev -> type == REDIR && current -> type == PIPE)
		culprit = current -> str;
	else if (prev && prev -> type == PIPE && current -> type == PIPE)
		culprit = current -> str;
	if (culprit)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", culprit);
		return (1);
	}
	else
		return (0);
}

int	syntax_check(t_token *toklist)
{
	t_token	*prev;

	prev = NULL;
	if (!toklist)
		return (0);
	while (toklist)
	{
		if (synt_err(prev, toklist))
			return (1);
		else
		{
			prev = toklist;
			toklist = toklist -> next;
		}
	}
	if (synt_err(prev, toklist))
		return (1);
	else
		return (0);
}
