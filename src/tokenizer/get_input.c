/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:17:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/04 10:43:09 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "signals.h"

static int	last_token_is_pipe(t_token *token_lst)
{
	t_token	*ptr;

	if (!token_lst)
		return (0);
	ptr = token_lst;
	while (ptr && ptr -> next)
		ptr = ptr -> next;
	if (ptr -> type == PIPE)
		return (1);
	else
		return (0);
}

static void	append_token_lst(t_token *old, t_token *new)
{
	while (old && old -> next)
		old = old -> next;
	old -> next = new;
}

static char	*join_and_free(char *old, char *new)
{
	char	*ptr;

	ptr = ft_strjoin(old, new);
	free(old);
	free(new);
	return (ptr);
}

static char	*get_further_input(t_token *token_lst, char *prev, t_list *envir, int exit_status)
{
	char	*line;
	t_token	*new_tok_lst;

	while (last_token_is_pipe(token_lst))
	{
		line = readline("> ");
		if (!line)
			return (prev);
		new_tok_lst = tokenizer(envir, line, exit_status);
		prev = join_and_free(prev, line);
		append_token_lst(token_lst, new_tok_lst);
		if (syntax_check(token_lst, 0))
			break ;
	}
	return (prev);
}

t_token	*get_full_token_lst(t_list *envir, int exit_status)
{
	t_token	*token_lst;
	char	*line;

	
	line = readline("minishell$ ");
	if (!line)
		exit(0);
	token_lst = tokenizer(envir, line, exit_status);
	if (!syntax_check(token_lst, 0) && last_token_is_pipe(token_lst))
		line = get_further_input(token_lst, line, envir, exit_status);
	if (*line != '\0' && !is_space(*line))
		add_history(line);
	free(line);
	return (token_lst);
}
