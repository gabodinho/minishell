/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:55:24 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/16 02:51:33 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	del_arr(char **arr)
{
	char	**ptr;

	ptr = arr;
	while (*arr)
		free(*arr++);
	free(ptr);
}

t_list	*get_env(char **envp)
{
	t_list	*start;

	start = NULL;
	while (*envp)
		ft_lstadd_back(&start, ft_lstnew(ft_strdup(*envp++)));
	return (start);
}

void	print_env(t_list *envlist)
{
	while (envlist)
	{
		printf("%s\n", (char *) envlist -> content);
		envlist = envlist -> next;
	}
}

char	*search_env(char *key, t_list *envir)
{
	while (strncmp(envir -> content, key, ft_strlen(key)))
		envir = envir -> next;
	if (!envir)
		return (NULL);
	else
		return (envir -> content + ft_strlen(key) + 1);
}

char	**conv_env(t_list *envir)
{
	int		count;
	int		i;
	char	**env_arr;

	i = 0;
	if (!envir)
		return (NULL);
	count = ft_lstsize(envir);
	env_arr = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		env_arr[i++] = ft_strdup((char *) envir -> content);
		envir = envir -> next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
