/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:17:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 09:28:38 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

void	expander(t_list *env, t_token *token, int exit_status);

t_token	*tokenizer(t_list *env, char *line, int exit_status)
{
	t_token	*token_lst;

	token_lst = tokenize_line(line);
	expander(env, token_lst, exit_status);
	return (token_lst);
}
/*
void print_token_list(t_token *token_lst)
{
    while (token_lst)
	{
        printf("Type: %d, Identifier: %s\n", token_lst->type, token_lst->str);
		token_lst = token_lst->next;
    }
}*/
