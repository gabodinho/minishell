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
#include "exit.h"

int	g_exit_status = 0;

// including the flag -lreadline to work!

// under construction!!
static int	execute_cmds(t_node *tree, t_list **envir, int prev_status)
{
	int	status;
	int	pid;
	(void)	prev_status;	//reactivate for further use

	pid = fork();
	if (pid < 0)
		panic("fork");
	else if (pid == 0)
		run_tree(tree, envir);	//hand prev status to execution
	else
		waitpid(pid, &status, 0);
	return (get_exit_status(status));
}

int main(int argc, char *argv[], char *envp[])
{
    //char *line = "echo 'Hello, World!' > output.txt";
    t_token *token_lst;
	t_node	*tree;
	t_list	*envir;
	char	*line;
	int		exit_status;
	(void) argc;
	(void) argv;

	envir = get_env(envp);
	exit_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			panic("readline");
		if (line[0] != '\0' && !is_space(line[0]))
			add_history(line);
		token_lst = tokenizer(envir, line, exit_status);
		tree = parse_pipe(&token_lst, envir);
		if (!syntax_check(token_lst))
			exit_status = execute_cmds(tree, &envir, exit_status);
		else
			exit_status = 127;
		free(line);
		clear_tree(tree);
		clear_list(&token_lst);
	}
}
