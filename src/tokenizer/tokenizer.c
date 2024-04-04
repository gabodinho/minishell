/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:17:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/04 13:09:16 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

void	expander(t_list *env, t_token *token, int exit_status);

t_token	*tokenizer(t_list *env, char *line, int exit_status)
{
	t_token	*token_lst;
	//t_token	*current_token;

	token_lst = tokenize_line(line);
	/*current_token = token_lst;

	while (current_token != NULL)
	{
		if (strchr(current_token->str, '\''))
			handle_single_quotes(current_token->str);
		else if (strchr(current_token->str, '"'))
			handle_double_quotes1(current_token->str);
		current_token = current_token->next; // Avanzar al siguiente token
	}*/
	
	expander(env, token_lst, exit_status);
	return (token_lst); // Devuelve la lista de tokens
}

void print_token_list(t_token *token_lst)
{
    while (token_lst)
	{
        printf("Type: %d, Identifier: %s\n", token_lst->type, token_lst->str);
		token_lst = token_lst->next;
    }
}
