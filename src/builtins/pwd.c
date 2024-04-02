/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:51:39 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/02 11:27:08 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	if_pflag_is_one(char *path)
{
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
}

char	*our_pwd(char **av, int pflag)
{
	char	*path;
	char	path1[1024];
	int		i;
	int		exit_status;

	i = 0;
	path = malloc(1024 * sizeof(char));
	if (has_options(av))
	{
		ft_putstr_fd("minishell: pwd: no options allowed\n", 2);
		exit_status = 1;
		return (NULL);
	}
	while (av[i] != NULL && av[i])
		i++;
	if (getcwd(path1, sizeof(path1)) == NULL)
	{
		perror("getcwd");
		exit_status = 127;
		return (NULL);
	}
	if (ft_strcmp(av[0], "pwd") == 0 || i > 1)
		printf("%s\n", path1);
	exit_status = 0;
	ft_strlcpy(path, path1, ft_strlen(path1) + 1);
	if (pflag == 1)
		if_pflag_is_one(path);
	else
		return (path);
	exit_status = 0;
	exit(exit_status);
	return (NULL);
}
