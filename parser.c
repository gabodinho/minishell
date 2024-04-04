/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:51:44 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/04 13:18:02 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_words(t_token *token)
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

t_node	*heredoc_cmd(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node -> ntype = N_HERE;
	node -> subnode = NULL;
	if (token -> next && (token -> next)-> type == WORD)
		node -> delim = (token -> next)-> str;
	else
		node -> delim = NULL;		// check error handling in og function
	return (node);
}

t_node	*redir_cmd(t_token *token)
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
		node -> file = (token -> next)-> str;		// check for error handling in og
	else
		node -> file = NULL;
	return (node);
}

t_node	*pipe_cmd(t_token **left_list, t_token **right_list, t_list *envir)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node -> ntype = N_PIPE;
	node -> left = parse_exe(left_list, envir);
	node -> right = parse_pipe(right_list, envir);
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

t_node	*init_node(t_list *envir, int words)
{
	t_node	*node;
	int			i;

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

void	add_attribute(t_node *node, char *str)
{
	int	i;

	i = 0;
	while ((node -> param)[i])
		i++;
//	if (i == 20)
//		panic("param limit in exec node");		// wip
	(node -> param)[i] = str;
}

void handle_double_quotes(char *str)
{
	size_t	i;

	i = ft_strlen(str);
	if (i >= 2 && ((str[0] == '"' && str[i - 1] == '"') || (str[0] == '\'' && str[i - 1] == '\'')))
	{
		ft_memmove(str, str + 1, i - 2);
		str[i - 2] = '\0';
	}
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
		else if (token -> type == DQUOTE)
		{
			handle_double_quotes(token -> str);
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

// returns pipe node with two children or exec node with one child
t_node	*parse_pipe(t_token **toklist, t_list *envir)
{
	t_node	*cmd;
	t_token	*token;

	token = *toklist;
	if (!token)
		return (NULL);
	while (token && token -> type != PIPE)
		token = token -> next;
	if (token && token -> type == PIPE)		// create pipe node
		cmd = pipe_cmd(toklist, &(token -> next), envir);
	else		// create (left) exec node
		cmd = parse_exe(toklist, envir);
	return (cmd);
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
				printf("\tmode: %d, fd: %d, file: %s\n", tree -> mode, tree -> fd, tree -> file);
			else if (tree -> ntype == N_HERE)
				printf("\theredoc with delim: %s\n", tree -> delim);
			tree = tree -> subnode;
		}
	}
	return ;
}
