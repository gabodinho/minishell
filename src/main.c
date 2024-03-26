/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:12:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/25 15:16:17 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "expander.h"

int	g_exit_status = 0;
<<<<<<< HEAD
/*
=======

>>>>>>> main
// including the flag -lreadline to work!

int main(int argc, char *argv[], char *envp[])
{
    //char *line = "echo 'Hello, World!' > output.txt";
    t_token *token_lst;
	t_node	*tree;
	char	*line;
	t_list	*envir;
	(void) argc;
	(void) argv;

	envir = get_env(envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (line[0] != '\0' && !is_space(line[0]))
			add_history(line);			//only add non empty lines to hist
		token_lst = tokenizer(envir, line);
		tree = parse_pipe(&token_lst, envir);
		print_token_list(token_lst);
		print_tree(tree);
		if (fork() == 0)
		{
			if (syntax_check(token_lst))
				exit(EXIT_FAILURE);
//			printf("syntax check passed\n");
//			run_tree(parse_pipe(&token_lst));
			run_tree(tree, &envir);
		}
		wait(0);
		free(line);
		clear_tree(tree);
		clear_list(&token_lst);
	}
    return 0;
<<<<<<< HEAD
}
*/

// including the flag -lreadline to work!

int main(int argc, char *argv[], char *envp[])
{
    //char *line = "echo 'Hello, World!' > output.txt";
    t_token *token_lst;
	t_node	*tree;
	char	*line;
	t_list	*envir;
//	pid_t	pid;
	(void) argc;
	(void) argv;

	envir = get_env(envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (line[0] != '\0' && !is_space(line[0]))
			add_history(line);			//only add non empty lines to hist
		token_lst = tokenizer(envir, line);
		tree = parse_pipe(&token_lst, envir);
		print_token_list(token_lst);
		print_tree(tree);
		if (tree -> ntype == N_EXE)
			exec_builtins(tree -> param, envir);
// 		pid = fork();
// 		if (!pid)
// 		{
// 			if (syntax_check(token_lst))
// 				exit(EXIT_FAILURE);
// //			printf("syntax check passed\n");
// //			run_tree(parse_pipe(&token_lst));
// 			run_tree(tree, envir);
// 		}
// 		else
// 			waitpid(pid, &status, 0);
		free(line);
		clear_tree(tree);
		clear_list(&token_lst);
	}
	clear_history();
    return(0);
=======
>>>>>>> main
}

