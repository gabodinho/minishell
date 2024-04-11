/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 23:49:54 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/11 02:39:42 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_words(t_token *token)
{
	int	res;

	res = 0;
	while (token)
	{
		if (token -> type == PIPE)
			break ;
		else if (token -> type == WORD)
		{
			res++;
			token = token -> next;
		}
		else if (token -> type == REDIR)
			token = token -> next -> next;
		else
			token = token -> next;
	}
	return (res);
}

static void	add_attribute(t_node *node, char *str)
{
	int	i;

	i = 0;
	while ((node -> param)[i])
		i++;
	(node -> param)[i] = str;
}

static t_node	*init_node(t_list *envir, int words)
{
	t_node	*node;
	int		i;

	node = malloc(sizeof(t_node));
	i = 0;
	node -> ntype = N_EXE;
	node -> subnode = NULL;
	node -> envir = envir;
	node -> param = malloc(sizeof(char *) * (words + 1));
	while (i <= words)
		(node -> param)[i++] = NULL;
	return (node);
}

t_node	*parse_exe(t_token **toklist, t_list *envir)
{
	t_node		*execmd;
	t_node		*redircmd;
	t_token		*token;

	if (!*toklist)
		return (NULL);
	execmd = init_node(envir, count_words(*toklist));
	token = *toklist;
	redircmd = NULL;
	while (token)
	{
		if (token -> type == PIPE)
			break ;
		else if (token -> type == WORD)
		{
			add_attribute(execmd, token -> str);
			token = token -> next;
		}
		else if (token -> type == REDIR)
			redircmd = parse_redir(redircmd, &token);
		else
			panic("unrecognized token");
	}
	add_attribute(execmd, NULL);
	return (add_last(redircmd, execmd));
}
