/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:39:49 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 14:11:53 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "expander.h"

static char	*expand_str(t_exp *exp, t_list *env, int exit_status)
{
	int			start_d;
	int			end_d;
	char		*new_str;
	char		*str;

	if (exp -> quotes == '\'')
		return (ft_strdup(exp -> str));
	str = ft_strdup(exp -> str);
	start_d = is_token_in_env(str);
	while (start_d != -1)
	{
		end_d = find_dollar(str, start_d + 1);
		new_str = create_string(env, str, start_d, end_d, exit_status);
		free(str);
		str = new_str;
		start_d = is_token_in_env(str);
	}
	return (str);
}

void	expander(t_list *env, t_token *token, int exit_status)
{
	t_exp		*exp_tok;
	t_exp		*ptr;
	char		*res;

	while (token)
	{
		res = NULL;
		exp_tok = split_quotes(token -> str);
		ptr = exp_tok;
		while (ptr)
		{
			res = join_and_free(res, expand_str(ptr, env, exit_status));
			ptr = ptr -> next;
		}
		free(token -> str);
		token -> str = res;
		clear_exp(&exp_tok);
		token = token -> next;
	}
}
