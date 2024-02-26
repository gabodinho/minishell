/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:17:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/26 12:57:00 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*tokenizer(void)
{
	t_token	*token_lst;
	char	*line;

	line = readline("minishell$ ");
	if (!line)
		return (NULL);
	add_history(line);
	token_lst = tokenize_line(line);
	free(line);
	return (token_lst);
}

void print_token_list(t_token *token_lst) 
{
    while (token_lst) 
	{
        printf("Type: %d, Identifier: %s\n", token_lst->type, token_lst->str);
		token_lst = token_lst->next;
    }
}

int main(void) 
{
    //char *line = "echo 'Hello, World!' > output.txt";
    t_token *token_lst;
	while (1)
	{
    	token_lst = tokenizer();
    	print_token_list(token_lst);
	}	
	clear_list(&token_lst);
    return 0;
}