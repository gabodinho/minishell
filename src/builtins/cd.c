/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:53:04 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/24 16:09:04 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Función para cambiar el directorio actual
char	*change_directory(char *new_dir)
{
	if (chdir(new_dir) == -1)
	{
		perror("chdir");
		return (NULL);
	}
	return (getcwd(NULL, 0));
}
// Función para actualizar una variable de entorno existente
void	update_existing_environment_variable(t_list *env_list, const char *key,
	const char *value)
{
	size_t	key_len;
	char	*env_key;
	char	*entry;

	key_len = ft_strlen(key);
	env_key = malloc(key_len + ft_strlen(value) + 1);
	if (env_key == NULL)
	{
		perror("malloc");
		return ;
	}
	sprintf(env_key, "%s%s", key, value);
	while (env_list)
	{
		entry = (char *)env_list->content;
		if (ft_strncmp(entry, key, key_len) == 0)
		{
			//free(entry);
			env_list->content = env_key;
			return ;
		}
		env_list = env_list->next;
	}
}

// Función para agregar una nueva variable de entorno
void	add_new_environment_variable(t_list **env_list, const char *key,
	const char *value)
{
	size_t	key_len;
	char	*env_key;
	t_list	*new_entry;

	key_len = ft_strlen(key);
	env_key = malloc(key_len + ft_strlen(value) + 1);
	if (env_key == NULL)
		return ;
	sprintf(env_key, "%s%s", key, value);
	new_entry = malloc(sizeof(t_list));
	if (new_entry == NULL)
	{
		free(env_key);
		return ;
	}
	new_entry->content = env_key;
	new_entry->next = NULL;
	while (*env_list && (*env_list)->next)
		*env_list = (*env_list)->next;
	if (*env_list)
		(*env_list)->next = new_entry;
	else
		*env_list = new_entry;
}

// Función principal para actualizar una variable de entorno
void	update_environment_variable(t_list **env_list, const char *key,
	const char *value)
{
	if (*env_list == NULL)
		add_new_environment_variable(env_list, key, value);
	else
		update_existing_environment_variable(*env_list, key, value);
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
		return ;
	}
	if (av[1] != NULL)
		new_dir = av[1];
	else
		new_dir = getenv("HOME");
	new_pwd = change_directory(new_dir);
	if (new_pwd == NULL)
	{
		free(old_pwd);
		return ;
	}
	update_environment_variable(&env_list, "PWD=", new_pwd);
	update_environment_variable(&env_list, "OLDPWD=", old_pwd);
	free(old_pwd);
	free(new_pwd);
}
