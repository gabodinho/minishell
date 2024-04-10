/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:23:23 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 09:41:30 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*create_token(char *content, int type)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (content)
		token->str = ft_strdup(content);
	else
		token->str = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	token_lst_add_back(t_token **token_lst, t_token *new)
{
	t_token	*now;

	if (!*token_lst)
	{
		*token_lst = new;
		return ;
	}
	now = *token_lst;
	while (now && now->next)
		now = now->next;
	now->next = new;
	new->prev = now;
}

void	clear_list(t_token **token_lst)
{
	t_token	*now;
	t_token	*next;

	now = *token_lst;
	if (!now)
		return ;
	while (now)
	{
		free(now->str);
		next = now->next;
		free(now);
		now = next;
	}
	*token_lst = NULL;
}
