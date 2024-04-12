/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:53:04 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/12 17:05:23 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_new_directory(char **av, t_list *env_list)
{
	char	*new_dir;
	char	*home;

	if (av[1] == NULL || ft_strcmp(av[1], "~") == 0)
		new_dir = get_env_var("HOME", env_list);
	else if (av[1][0] == '-' && av[1][1] == '\0')
		new_dir = get_env_var("OLDPWD", env_list);
	else if (av[1][0] == '~' && av[1][1] == '/')
	{
		home = get_env_var("HOME", env_list);
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
		new_dir = ft_strjoin(home, av[1] + 1);
		if (!new_dir)
		{
			perror("malloc");
			return (NULL);
		}
	}
	else
		new_dir = av[1];
	return (new_dir);
}

char	*change_directory_and_get_new_pwd(char *new_dir)
{
	char	*new_pwd;

	new_pwd = NULL;
	if (!new_dir || access(new_dir, F_OK) == -1)
	{
		if (new_dir)
			printf("cd: %s: No such file or directory\n", new_dir);
		return (NULL);
	}
	new_pwd = change_directory(new_dir);
	if (!new_pwd)
		printf("cd: %s: No such file or directory\n", new_dir);
	return (new_pwd);
}

int	our_cd_internal(char **av, t_list *env_list, char *old_pwd)
{
	char	*new_dir;
	char	*new_pwd;

	new_dir = get_new_directory(av, env_list);
	if (!new_dir)
	{
		free(old_pwd);
		return (1);
	}
	new_pwd = change_directory_and_get_new_pwd(new_dir);
	if (!new_pwd)
	{
		free(old_pwd);
		if (av[1][0] == '~' && av[1][1] == '/')
			free(new_dir);
		return (1);
	}
	update_environment_variable(&env_list, "PWD=", new_pwd);
	update_environment_variable(&env_list, "OLDPWD", old_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}

// Función principal para el comando cd
int	our_cd(char **av, t_list *env_list)
{
	char	*old_pwd;
	int		result;

	old_pwd = ft_strdup(get_env_var("PWD", env_list));
	if (!old_pwd)
	{
		perror("getcwd");
		return (1);
	}
	result = our_cd_internal(av, env_list, old_pwd);
	return (result);
}

/* Función para el comando cd
int	our_cd(char **av, t_list *env_list)
{
	char	*old_pwd;
	char	*new_dir;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		perror("getcwd");
		return (1);
	}
	if (av[1] != NULL)
		new_dir = av[1];
	else
		new_dir = getenv("HOME");
	if (access(new_dir, F_OK) == -1)
	{
		free(old_pwd);
		return (1);
	}
	new_pwd = change_directory(new_dir);
	if (new_pwd == NULL)
	{
		free(old_pwd);
		return (1);
	}
	update_environment_variable(&env_list, "PWD=", new_pwd);
	update_environment_variable(&env_list, "OLDPWD=", old_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
*/

/*
int	our_cd_internal(char **av, t_list *env_list, char *old_pwd)
{
	char	*new_dir;
	char	*new_pwd;
	char	*home;

	if (av[1] == NULL || ft_strcmp(av[1], "~") == 0)
		new_dir = getenv("HOME");
	else if (av[1][0] == '-' && av[1][1] == '\0')
	{
		new_dir = getenv("OLDPWD");
		if (!new_dir)
		{
			printf("cd: OLDPWD not set\n");
			free(old_pwd);
			return (1);
		}
	}
	else if (av[1][0] == '~' && av[1][1] == '/')
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			free(old_pwd);
			return (1);
		}
		new_dir = ft_strjoin(home, av[1] + 1);
		if (!new_dir)
		{
			perror("malloc");
			free(old_pwd);
			return (1);
		}
	}
	else
		new_dir = av[1];
		
	//if (av[1] != NULL)
	//	new_dir = av[1];
	//else
	//	new_dir = getenv("HOME");
	if (!new_dir || access(new_dir, F_OK) == -1)
	{
		printf("cd: %s: No such file or directory\n", new_dir);
		free(old_pwd);
		return (1);
	}
	new_pwd = change_directory(new_dir);
	if (!new_pwd)
	{
		printf("cd: %s: No such file or directory\n", new_dir);
		free(old_pwd);
		return (1);
	}
	update_environment_variable(&env_list, "PWD=", new_pwd);
	update_environment_variable(&env_list, "OLDPWD=", old_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}*/