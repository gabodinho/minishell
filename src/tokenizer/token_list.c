/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:23:23 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/05 16:16:16 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*create_token(char *content, int type)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	if (content)
	{
		//if (type == DGREAT || type == DLESS)
		if (type == REDIR)
			token->str = ft_strdup(content);
		else
			token->str = content;
	}
	token->type = type;
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
