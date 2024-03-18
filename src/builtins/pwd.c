/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:51:39 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/18 13:38:18 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	if_pflag_is_one(char *path)
{
	write(1, path, b_strlen(path));
	write(1, "\n", 1);
	free(path);
	g_exit_status = 0;
	return ;
}

char	*our_pwd(char **av, int pflag)
{
	char	*path;
	char	path1[1024];
	int		i;

	i = 0;
	path = malloc(1024 * sizeof(char));
	while (av[i] != NULL && av[i])
		i++;
	if (i > 1)
	{
		printf("pwd: too many arguments!\n");
		return (NULL);
	}
	if (getcwd(path1, sizeof(path1)) == NULL)
	{
		perror("getcwd");
		g_exit_status = 127;
		return (NULL);
	}
	if (ft_strcmp(av[0], "pwd") == 0)
		printf("%s\n", path1);
	g_exit_status = 0;
	ft_strlcpy(path, path1, b_strlen(path1) + 1);
	if (pflag == 1)
		if_pflag_is_one(path);
	else
		return (path);
	g_exit_status = 0;
	exit(g_exit_status);
	return (NULL);
}