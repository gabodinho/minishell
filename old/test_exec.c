/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:59:26 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/07 16:13:14 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;
	char	*av[64];
	int		ac;
	char	*token;
	pid_t	pid;
	
	while (1)
	{
		input = readline("minishell> ");
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		ac = 0;
		token = strtok(input, " ");
		while (token && ac < 64 - 1)
		{
			av[ac] = token;
			ac++;
			token = strtok(NULL, " ");
		}
		av[ac] = NULL;
		pid = fork();
		if (pid == 0)
		{
			execve(av[0], av, NULL);
			perror("execve");
			exit(1);
		}
		else if(pid > 0)
			wait(NULL);
		else
			perror("fork");
		free(input);
	}
	return (0);
}

/*
int	main()
{
	char *av[] = {"ls", "-l", NULL};
	char *envp[] = {NULL};

	if (execve("/bin/ls", av, envp) == -1)
	{
		perror("execve");
		return (1);
	}
	return (0);
}*/