/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:23:23 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/22 17:26:53 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*create_token(char *content, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = content;
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