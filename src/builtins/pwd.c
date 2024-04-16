/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:51:39 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 13:05:29 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	if_pflag_is_one(char *path)
{
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
}

int	handle_pwd_options(void)
{
	ft_putstr_fd("minishell: pwd: no options allowed\n", 2);
	return (1);
}

int	handle_getcwd_error(void)
{
	perror("getcwd");
	return (127);
}

int	our_pwd(char **av, int pflag, t_list *env)
{
	char	*path;
	char	*path1;
	int		i;
	int		exit_status;

	i = 0;
	path = malloc(1024 * sizeof(char));
	if (has_options(av))
		return (handle_pwd_options());
	while (av[i] != NULL && av[i])
		i++;
	path1 = get_env_var("PWD", env);
	if (!path1)
		return (handle_getcwd_error());
	if (ft_strcmp(av[0], "pwd") == 0 || i > 1)
		printf("%s\n", path1);
	exit_status = 0;
	ft_strlcpy(path, path1, ft_strlen(path1) + 1);
	if (pflag == 1)
		if_pflag_is_one(path);
	else
		free(path);
	return (exit_status);
}
