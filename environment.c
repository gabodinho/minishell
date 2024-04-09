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
/*
static int	is_valid_env_name(const char *name)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*name) && *name != '_')
        return (1);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	lst_rm_one(t_list **start, int i)
{
	t_list	*temp;
	t_list	*temp2;

	temp = *start;
	printf("eingang");
	if (i == 0)
	{
		*start = temp -> next;
		free(temp -> content);
		free(temp);
	}
	else
	{
		while (1 < i-- && temp)
			temp = temp -> next;
		printf("var = %s\n", (char *) temp -> next -> content);
		if (temp -> next)
		{
			printf("yep\n");
			temp2 = (temp -> next) -> next;
			printf("new next: %s\n", (char *) temp2 -> content);
//			free((temp -> next) -> content);
//			free(temp -> next);
			temp -> next = temp2;
		}
	}
	printf("ausgang");
}


void	ft_unset(char **param, t_list **envir)
{
	int		i;
	char	*errmsg;
	t_list	*temp;

	temp = *envir;
	errmsg = NULL;
	while (*++param)
	{
		printf("testtest: %s", *param);
		if (!errmsg && is_valid_env_name(*param))
			errmsg = *param;
		else
		{
			temp = *envir;
			i = 0;
			while (temp)
			{
				if (!ft_strncmp(temp -> content, *param, ft_strlen(*param)))
				{
					lst_rm_one(envir, i);
					break ;
				}
				temp = temp -> next;
				i++;
			}
		}
	}
	print_env(*envir);
	if (errmsg)
		panic(errmsg);
	else
		exit(EXIT_SUCCESS);
}
*/




























