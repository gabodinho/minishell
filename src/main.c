/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:12:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/22 10:30:35 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "expander.h"
#include "execution.h"
#include "builtins.h"
#include "signals.h"

int	g_signal;

static int	execute_non_builtin_commands(t_data *data)
{
	int		status;
	int		pid;

	status = 0;
	pid = fork();
	if (pid < 0)
		panic("fork", errno);
	else if (pid == 0)
		run_tree(data -> tree, data);
	else
	{
		traverse_tree(data -> tree, data, close_pfds);
		waitpid(pid, &status, 0);
	}
	return (get_exit_status(status));
}

static int	execute_cmds(t_data *data)
{
	if (!(data -> tree))
		return (0);
	traverse_tree(data -> tree, data, prepare_heredoc);
	if (g_signal != 0)
		return (g_signal);
	set_signals_cmd();
	if (!is_builtin_exec(data -> tree))
		return (run_builtin_tree(data));
	else
		return (execute_non_builtin_commands(data));
}

/*
static int	execute_cmds(t_data *data)
{
	int	status;
	int	pid;

	status = 0;
	if (!(data -> tree))
		return (0);
	traverse_tree(data -> tree, prepare_heredoc);
	if (g_signal != 0)
		return (g_signal);
	set_signals_cmd();
	if (!is_builtin_exec(data -> tree))
		return (run_builtin_tree(data));
	else
	{
		pid = fork();
		if (pid < 0)
			panic("fork", errno);
		else if (pid == 0)
			status = run_tree(data -> tree, data);
		else
		{
			traverse_tree(data -> tree, close_pfds);
			waitpid(pid, &status, 0);
		}
		return (get_exit_status(status));
	}
}*/

static t_token	*get_token_lst(t_list *envir, int *exit_status)
{
	t_token	*token_lst;
	t_node	*tree;
	t_data	*s_data;

	g_signal = 0;
	set_signals_main();
	token_lst = get_full_token_lst(envir, *exit_status);
	if (!syntax_check(token_lst, 1))
	{
		tree = parse_pipe(&token_lst, envir);
		s_data = get_data(&token_lst, &envir, tree);
		*exit_status = execute_cmds(s_data);
		clear_tree(tree);
		free(s_data);
	}
	else
		*exit_status = 127;
	return (token_lst);
}

static int	run_shell_loop(t_list *envir)
{
	int		exit_status;
	t_token	*token_lst;

	while (1)
	{
		token_lst = get_token_lst(envir, &exit_status);
		if (g_signal && !exit_status)
			exit_status = g_signal;
		clear_list(&token_lst);
	}
	return (exit_status);
}
/*
static void	run_shell(t_list *envir)
{
	t_token	*token_lst;
	t_node	*tree;
	t_data	*data;
	int		exit_status;

	exit_status = 0;
	while (1)
	{
		g_signal = 0;
		set_signals_main();
		token_lst = get_full_token_lst(envir, exit_status);
		if (!syntax_check(token_lst, 1))
		{
			tree = parse_pipe(&token_lst, envir);
			print_tree(tree);
			data = get_data(&token_lst, &envir, tree);
			exit_status = execute_cmds(data);
			clear_tree(tree);
			free(data);
		}
		else
			exit_status = 127;
		if (g_signal && !exit_status)
			exit_status = g_signal;
		clear_list(&token_lst);
	}
}*/

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*envir;

	(void) argv;
	if (argc > 1)
	{
		printf("no parameters allowed\n");
		return (1);
	}
	welcome_message();
	envir = get_env(envp);
	run_shell_loop(envir);
	return (0);
}

/*
int	main(int argc, char *argv[], char *envp[])
{
	t_token	*token_lst;
	t_node	*tree;
	t_list	*envir;
	t_data	*data;
	int		exit_status;

	(void) argc;
	(void) argv;
	envir = get_env(envp);
	exit_status = 0;
	suppress_output();
	while (1)
	{
		g_signal = 0;
		set_signals_main();
		token_lst = get_full_token_lst(envir, exit_status);
		tree = parse_pipe(&token_lst, envir);
		data = get_data(&token_lst, &envir, tree);
		if (!syntax_check(token_lst, 1))
			exit_status = execute_cmds(data);
		else
			exit_status = 127;
		clear_tree(tree);
		clear_list(&token_lst);
		free(data);
	}
}*/
