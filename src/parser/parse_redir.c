/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 23:52:56 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/10 23:59:54 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"

static t_node	*heredoc_cmd(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node -> ntype = N_HERE;
	node -> subnode = NULL;
	if (token -> next && (token -> next)-> type == WORD)
		node -> delim = (token -> next)-> str;
	else
		node -> delim = NULL;
	return (node);
}

static t_node	*redir_cmd(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node -> ntype = N_REDIR;
	node -> subnode = NULL;
	if (!ft_strncmp(token -> str, "<", 1))
	{
		node -> mode = O_RDONLY;
		node -> fd = 0;
	}
	else
	{
		node -> fd = 1;
		if (!ft_strncmp(token -> str, ">>", 2))
			node -> mode = O_WRONLY | O_CREAT | O_APPEND;
		else
			node -> mode = O_WRONLY | O_CREAT | O_TRUNC;
	}
	if (token -> next && (token -> next)-> type == WORD)
		node -> file = (token -> next)-> str;
	else
		node -> file = NULL;
	return (node);
}

t_node	*parse_redir(t_node *cmd, t_token **toklist)
{
	t_node	*node;

	if (ft_strncmp((*toklist) -> str, "<<", 2))
	{
		node = redir_cmd(*toklist);
		if (node -> file)
			*toklist = (*toklist)-> next -> next;
		else
			*toklist = (*toklist)-> next;
	}
	else
	{
		node = heredoc_cmd(*toklist);
		if (node -> delim)
			*toklist = (*toklist)-> next -> next;
		else
			*toklist = (*toklist)-> next;
	}
	return (add_last(cmd, node));
}
