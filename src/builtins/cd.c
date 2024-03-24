/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:53:04 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/24 15:47:25 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
void	our_cd(char **av, t_list *env)
{
	char	*path;
	char	*env_entry;
	char	*new_entry;
	char	*old_entry;
	
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
		old_entry = (char *)(env->content);
		if (ft_strncmp(env_entry, "OLDPWD=", 7) == 0)
		{
			//free(env_entry);
			old_entry = ft_strjoin("OLDPWD=",path);
			if (old_entry == NULL)
			{
				perror("ft_strjoin");
				break ;
			}
			env->content = old_entry;
			break ;
		}
		env = env->next;
	}
	free(path);
	g_exit_status = 0;
}*/
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

// Función para cambiar el directorio actual
char	*change_directory(char *new_dir) 
{
	if (chdir(new_dir) == -1) 
	{
		perror("chdir");
		return NULL;
	}
	return (getcwd(NULL, 0));
}

// Función para actualizar una variable de entorno
void	update_environment_variable(t_list *env_list, const char *key, const char *value) 
{
	size_t	key_len;
	char	*env_key;
	char	*entry;
	t_list	*new_entry;
	
	key_len = strlen(key);
	env_key = malloc(key_len + strlen(value) + 1);
	if (env_key == NULL) 
	{
		perror("malloc");
		return;
	}
	sprintf(env_key, "%s%s", key, value);
	while (env_list) 
	{
		entry = (char *)env_list->content;
		if (strncmp(entry, key, key_len) == 0) 
		{
			//free(entry);
			env_list->content = env_key;
			return;
		}
		env_list = env_list->next;
	}
	// Si la variable de entorno no existe, la agregamos al final de la lista
	new_entry = malloc(sizeof(t_list));
	if (new_entry == NULL) 
	{
		perror("malloc");
		free(env_key);
		return;
	}
	new_entry->content = env_key;
	new_entry->next = NULL;
	while (env_list->next)
		env_list = env_list->next;
	env_list->next = new_entry;
}

// Función para el comando cd
void	our_cd(char **av, t_list *env_list) 
{
	char	*old_pwd;
	char	*new_dir;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL) 
	{
		perror("getcwd");
		return;
	}
	if (av[1] != NULL)
		new_dir = av[1];
	else
		new_dir = getenv("HOME");

	new_pwd = change_directory(new_dir);
	if (new_pwd == NULL)
	{
		free(old_pwd);
		return;
	}
	// Actualizar las variables de entorno PWD y OLDPWD
	update_environment_variable(env_list, "PWD=", new_pwd);
	update_environment_variable(env_list, "OLDPWD=", old_pwd);
	free(old_pwd);
	free(new_pwd);
}
