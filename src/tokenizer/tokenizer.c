/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:17:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/03 13:58:57 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	expander(t_list *env, t_token *token, int exit_status);

t_token	*tokenizer(t_list *env, char *line, int exit_status)
{
	t_token	*token_lst;

	token_lst = tokenize_line(line);
	expander(env, token_lst, exit_status);
	return (token_lst);
}

t_token	*get_last_token(t_token *token_lst)
{
	t_token	*ptr;

	ptr = token_lst;
	if (!token_lst)
		return (NULL);
	while (ptr && ptr -> next)
		ptr = ptr -> next;
	return (ptr);
}

int	last_token_is_pipe(t_token *token_lst)
{
	t_token	*ptr;

	ptr = get_last_token(token_lst);
	if (!ptr)
		return (0);
	if (ptr -> type == PIPE)
		return (1);
	else
		return (0);
}

char	*join_n_free(char *old, char *new)
{
	char	*line;

	line = ft_strjoin(old, new);
	free(old);
	free(new);
	return (line);
}

void	append_token_lst(t_token *old, t_token *new)
{
	while (old && old -> next)
		old = old -> next;
	old -> next = new;
}

t_token	*get_full_token_lst(t_list *envir, char **line, int exit_status)
{
	t_token	*token_lst;
	t_token	*token_lst_sufix;
	char	*new;

	token_lst = tokenizer(envir, *line, exit_status);
	while (1)
	{
		if (last_token_is_pipe(token_lst))
		{
			new = readline("> ");
			if (!new)
				return (perror("readline"), NULL);
			token_lst_sufix = tokenizer(envir, new, exit_status);
			*line = join_n_free(*line, new);
			append_token_lst(token_lst, token_lst_sufix);
		}
		else
			break ;
	}
	if (**line != '\0' && !is_space(**line))
		add_history(*line);
	return (token_lst);
}

		
/*
void	print_token_list(t_token *token_lst)
{
    while (token_lst)
	{
        printf("Type: %d, Identifier: %s\n", token_lst->type, token_lst->str);
		token_lst = token_lst->next;
    }
}*/
