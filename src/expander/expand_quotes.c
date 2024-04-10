/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:12:50 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 14:13:18 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	clear_exp_recu(t_exp *exp)
{
	if (exp -> next)
		clear_exp_recu(exp -> next);
	free(exp -> str);
	free(exp);
}

void	clear_exp(t_exp **exp)
{
	if (!*exp)
		return ;
	clear_exp_recu(*exp);
	*exp = 0;
}

t_exp	*new_exp(char *str, int quotes)
{
	t_exp	*new;

	new = malloc(sizeof(t_exp));
	if (!new)
		return (perror("new_exp: malloc"), NULL);
	new -> str = str;
	new -> quotes = quotes;
	new -> next = NULL;
	return (new);
}

void	exp_append(t_exp **start, char *str, int quotes)
{
	t_exp	*ptr;

	ptr = *start;
	if (!ptr)
	{
		*start = new_exp(str, quotes);
		return ;
	}
	while (ptr && ptr -> next)
		ptr = ptr -> next;
	ptr -> next = new_exp(str, quotes);
}
