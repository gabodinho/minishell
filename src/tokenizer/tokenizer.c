/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:17:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/05 15:29:40 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*tokenizer(char *line)
{
	t_token	*token_lst;

	token_lst = tokenize_line(line);
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
}

int main(void) 
{
    //char *line = "echo 'Hello, World!' > output.txt";
    t_token *token_lst;
	char	*line;
	
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		add_history(line);
    	token_lst = tokenizer(line);
    	print_token_list(token_lst);
		free(line);
		clear_list(&token_lst);
	}
    return 0;
}*/