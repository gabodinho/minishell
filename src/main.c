/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:12:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/11 17:03:10 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "expander.h"
#include "execution.h"
#include "builtins.h"
#include "signals.h"

int	g_signal;

static t_data	*get_data(t_token **toklst, t_list **envir, t_node *tree)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data -> tree = tree;
	data -> envir = envir;
	data -> tok_lst = toklst;
	return (data);
}

static int	execute_cmds(t_data *data)
{
	int	status;
	int	pid;

	status = 0;
	signal(SIGINT, signals_cmd);
	signal(SIGQUIT, signals_cmd);
	if (!(data -> tree))
		return (0);
	else if (!is_builtin_exec(data -> tree))
		return (run_builtin_tree(data));
	else
	{
		pid = fork();
		if (pid < 0)
			panic("fork");
		else if (pid == 0)
			status = run_tree(data -> tree, data);
		else
			waitpid(pid, &status, 0);
		return (get_exit_status(status));
	}
}

void	print_color_text(char *text, char *color)
{
	char	*color_code;

	color_code = "";
	if (ft_strcmp(color, "red") == 0)
		color_code = "\033[31m";
	else if (ft_strcmp(color, "green") == 0)
		color_code = "\033[32m";
	else if (ft_strcmp(color, "yellow") == 0)
		color_code = "\033[33m";
	write(1, color_code, strlen(color_code));
	write(1, text, strlen(text));
	write(1, "\033[0m", 4);
}

void	print_green_fosforito_text(void)
{
	char	*text;
	text =
		GREEN_FOSFORITO"\
		 _______ _________ _       _________ _______           _______   _        _       \n\
		(       )\\__   __/( (    /|\\__   __/(  ____ \\|\\     /||(  ____ \\( \\      ( \\      \n\
		| () () |   ) (   |  \\  ( |   ) (   | (    \\/| )   ( || (    \\/| (      | (      \n\
		| || || |   | |   |   \\ | |   | |   | (_____ | (___) || (__    | |      | |      \n\
		| |(_)| |   | |   | (\\ \\) |   | |   (_____  )|  ___  ||  __)   | |      | |      \n\
		| |   | |   | |   | | \\   |   | |         ) || (   ) || (      | |      | |      \n\
		| )   ( |___) (___| )  \\  |___) (___/\\____) || )   ( || (____/\\| (____/\\| (____/\\\n\
		|/     \\|\\_______/|/    )_)\\_______/\\_______)|/     \\|(_______/(_______/(_______/\n"RESET_COLOR;


	write(1, text, strlen(text));
}

void welcome_message(void) 
{
	char	*welcome_text;
	
	print_green_fosforito_text();
	welcome_text = "\nBy ggiertzu & irrivero-\n";
	print_color_text(welcome_text, "red");
	printf("\n");
}


static void	run_shell(t_list *envir)
{
	t_token	*token_lst;
	t_node	*tree;
	t_data	*data;
	int		exit_status;

	exit_status = 0;
//	suppress_output();
	while (1)
	{
		g_signal = 0;
		set_signals_main();
		token_lst = get_full_token_lst(envir, exit_status);
		if (!syntax_check(token_lst, 1))
		{
			tree = parse_pipe(&token_lst, envir);
			data = get_data(&token_lst, &envir, tree);
			exit_status = execute_cmds(data);
			clear_tree(tree);
			free(data);
		}
		else
			exit_status = 127;
		clear_list(&token_lst);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*envir;

	(void) argc;
	(void) argv;
	welcome_message();
	envir = get_env(envp);
	run_shell(envir);
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
