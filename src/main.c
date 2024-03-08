/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:12:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/05 16:46:21 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

// including the flag -lreadline to work!
int main(void) 
{
    //char *line = "echo 'Hello, World!' > output.txt";
    t_token *token_lst;
	t_node	*tree;
	char	*line;
	
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		add_history(line);
    	token_lst = tokenizer(line);
		tree = parse_pipe(&token_lst);
    	print_token_list(token_lst);
		print_tree(tree);
		if (fork() == 0)
			run_tree(tree);
		wait(0);
		free(line);
		clear_tree(tree);
		clear_list(&token_lst);
	}
    return 0;
}