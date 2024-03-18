/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:53:04 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/18 15:17:51 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	our_cd(char **av, t_list *env)
{
	char	*path;
	char	*env_entry;
	char	*new_entry;
	
	if (!av[1])
	{
		if (chdir(getenv("HOME")) == -1)
			perror("cd");
	}
	else
	{
		if (chdir(av[1]) == -1)
			perror("cd");
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("getcwd");
		return ;
	}
	while (env != NULL)
	{
		env_entry = (char *)(env->content);
		if (ft_strncmp(env_entry, "PWD=", 4) == 0)
		{
			//free(env_entry);
			new_entry = ft_strjoin("PWD=",path);
			if (new_entry == NULL)
			{
				perror("ft_strjoin");
				break ;
			}
			env->content = new_entry;
			break ;
		}
		env = env->next;
	}
	free(path);
	g_exit_status = 0;
}

/*
void	our_cd(char **av)
{
	int		i;
	char	*path;

	i = chdir(av[1]);
	path = ft_strjoin(ft_strdup(strerror(errno)), ft_strdup("\n"));
	if (i == -1)
		write(2, path, ft_strlen(path) + 1);
	if (path)
		free(path);
	g_exit_status = 0;
}*/