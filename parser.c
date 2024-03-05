/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:51:44 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/03 20:05:27 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node    *heredoc_cmd(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node -> ntype = N_HERE;
	if (token -> next && (token -> next) -> type == WORD)
		node -> delim = (token -> next) -> str;
	else
		node -> delim = NULL;		// check error handling in og function
	return (node);
}

t_node	*redir_cmd(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node -> ntype = N_REDIR;
	if (ft_strncmp(token -> str, "<", 1))
	{
		node -> mode = O_RDONLY;
		node -> fd = 0;
	}
	else if (ft_strncmp(token -> str, ">", 1))
	{
		node -> mode = O_CREAT;
		node -> fd = 1;
	}
	else
	{
		node -> mode = O_APPEND;
		node -> fd = 1;
	}
	if (token -> next && (token -> next) -> type == WORD)
		node -> file = (token -> next) -> str;		// check for error handling in og
	else
		node -> file = NULL;
	return (node);
}

t_node	*pipe_cmd(t_token **left_list, t_token **right_list)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node -> ntype = N_PIPE;
	node -> left = parse_exe(left_list);
	node -> right = parse_pipe(right_list);
	return (node); 
}

t_node    *parse_redir(t_node *cmd, t_token **toklist)
{
	t_node	*node;

	if (((*toklist) -> type == REDIR) && !ft_strncmp((*toklist) -> str, "<<", 2))
	{
		node = redir_cmd(*toklist);
		if (node -> file)
			*toklist = (*toklist) -> next -> next;
		else
			*toklist = (*toklist) -> next;
	}
	else if ((*toklist) -> type == REDIR)
	{
		node = heredoc_cmd(*toklist);		// wip (inkrement toklist)
		if (node -> delim)
			*toklist = (*toklist) -> next -> next;
		else
			*toklist = (*toklist) -> next;
	}
	else
		return (cmd);
	node -> subnode = cmd;
	return (node);
}

t_node	*init_node(void)
{
	t_node	*node;
	int			i;

	node = malloc(sizeof(t_node));
	i = 0;
	while (i < 20)
		(node -> param)[i] = NULL;
	return (node);
}

void	add_attribute(t_node *node, char *str)
{
	int	i;

	i = 0;
	while (i < 20 && (node -> param)[i])
		i++;
	if (i == 20)
		throw_error("param limit in exec node");		// wip
	else 
		(node -> param)[i] = str;
}

t_node	*parse_exe(t_token **toklist)
{
	t_node		*execmd;
	t_node		*cmd;
	t_token		*token;

	if (!*toklist)
		return (NULL);
	execmd = init_node();
	token = *toklist;
	cmd = parse_redir(execmd, &token);
	while (token)
	{
		if (token -> type == PIPE)
			break ;
		else if (token -> type == WORD)
			add_attribute(execmd, token -> str);
		token = token -> next;
		cmd = parse_redir(cmd, &token);
	}
	add_attribute(execmd, NULL);
	return (cmd);
}

// returns pipe node with two children or exec node with one child
t_node	*parse_pipe(t_token **toklist)
{
	t_node	*cmd;
	t_token	*token;

	token = *toklist;
	if (!token)
		return (NULL);
	while (token && token -> type != PIPE)
		token = token -> next;
	if (token && token -> type == PIPE)		// create pipe node
		cmd = pipe_cmd(toklist, &(token -> next));
	else		// create (left) exec node
		cmd = parse_exe(toklist);
	return (cmd);
}