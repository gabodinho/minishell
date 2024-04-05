/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:12:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/05 14:51:51 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "expander.h"
#include "signals.h"
#include "exit.h"

int	g_signal;
void	signals_cmd(int signum);

static int	execute_cmds(t_node *tree, t_list **envir)
{
	int	status;
	int	pid;

	status = 0;
	signal(SIGINT, signals_cmd);
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
	t_token *token_lst;
	t_node	*tree;
	t_list	*envir;
	int		exit_status;
	(void) argc;
	(void) argv;

	envir = get_env(envp);
	exit_status = 0;
	while (1)
	{
		g_signal = 0;
		set_signals_main();
		token_lst = get_full_token_lst(envir, exit_status);
		//print_token_list(token_lst);
		tree = parse_pipe(&token_lst, envir);
		if (!syntax_check(token_lst, 1))
			exit_status = execute_cmds(tree, &envir);
		else
			exit_status = 127;
		if (g_signal == SIGINT)
			exit_status = 128 + g_signal;
		clear_tree(tree);
		clear_list(&token_lst);
	}
}
