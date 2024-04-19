/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 23:29:33 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/11 02:38:01 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	panic(char *msg, int ret)
{
	perror(msg);
	exit(ret);
}

t_node	*add_last(t_node *redir, t_node *exec)
{
	t_node	*ptr;

	ptr = redir;
	if (!redir)
		return (exec);
	while (redir && redir -> subnode)
		redir = redir -> subnode;
	redir -> subnode = exec;
	return (ptr);
}

static int	synt_err(t_token *prev, t_token *current, int print_err)
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
		if (print_err)
			printf("minishell: \
syntax error near unexpected token `%s'\n", culprit);
		return (1);
	}
	else
		return (0);
}

int	syntax_check(t_token *toklist, int print_err)
{
	t_token	*prev;

	prev = NULL;
	if (!toklist)
		return (0);
	while (toklist)
	{
		if (synt_err(prev, toklist, print_err))
			return (1);
		else
		{
			prev = toklist;
			toklist = toklist -> next;
		}
	}
	if (synt_err(prev, toklist, print_err))
		return (1);
	else
		return (0);
}

void	clear_tree(t_node *tree)
{
	if (tree && tree -> ntype == N_PIPE)
	{
		clear_tree(tree -> left);
		clear_tree(tree -> right);
	}
	else if (tree)
		clear_tree(tree -> subnode);
	if (tree && tree -> ntype == N_EXE)
		free(tree -> param);
	if (tree)
		free(tree);
}

void	print_tree(t_node *tree)
{
	int	i;

	i = 0;
	while (tree)
	{
		if (tree && tree -> ntype == N_PIPE)
		{
			printf("Pipe node\nleft subtree:\n");
			print_tree(tree -> left);
			tree = tree -> right;
			printf("right subtree:\n");
		}
		else if (tree)
		{
			printf("node type: %d\n", tree -> ntype);
			if (tree -> ntype == N_EXE)
			{
				while (tree -> param[i] && i < 20)
					printf("\t%s\n", tree -> param[i++]);
			}
			else if (tree -> ntype == N_REDIR)
				printf("\tmode: %d, fd: %d, file: %s\n", \
tree -> mode, tree -> fd, tree -> file);
			else if (tree -> ntype == N_HERE)
				printf("\theredoc with delim: %s\n", tree -> delim);
			tree = tree -> subnode;
		}
	}
	return ;
}

