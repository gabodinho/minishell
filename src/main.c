/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:12:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/01 19:46:42 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "expander.h"
#include "signals.h"
#include "exit.h"

int	g_exit_status = 0;

static int	execute_cmds(t_node *tree, t_list **envir)
{
	int	status;
	int	pid;

	if (!tree)
		return (0);
	else if (!is_builtin_exec(tree))
		return (run_builtin_tree(tree, envir));
	else
	{
		pid = fork();
		if (pid < 0)
			panic("fork");
		else if (pid == 0)
			run_tree(tree, envir);
		else
			waitpid(pid, &status, 0);
		return (get_exit_status(status));
	}

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
	set_signals();
	exit_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			perror("readline");
		if (line[0] != '\0' && !is_space(line[0]))
			add_history(line);
		token_lst = tokenizer(envir, line, exit_status);
		tree = parse_pipe(&token_lst, envir);
		if (!syntax_check(token_lst))
			exit_status = execute_cmds(tree, &envir);
		else
			exit_status = 127;
		free(line);
		clear_tree(tree);
		clear_list(&token_lst);
	}
}
