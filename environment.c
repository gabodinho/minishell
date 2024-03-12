/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:55:24 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/12 21:43:25 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*get_env(char **envp)
{
	t_list	*start;

	while (*envp)
		ft_lstadd_back(&start, ft_lstnew(*envp++));
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
