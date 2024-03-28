/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:51:55 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/28 13:45:29 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	lst_rm(t_list **lst, int i)
{
	t_list	*tmp;
	t_list	*prev;
	int		count;

	if (!lst || !*lst)
		return ;
	tmp = *lst;
	prev = NULL;
	count = 0;
	while (tmp && count < i)
	{
		prev = tmp;
		tmp = tmp->next;
		count++;
	}
	if (!tmp)
		return ;
	if (prev)
		prev->next = tmp->next;
	else
		*lst = tmp->next;
	free(tmp);
}

void	unset_env_list(t_list **env_list, char **target_key)
{
	t_list	*temp;
	int		i;

	if (!target_key || !env_list)
		return ;
	while (*target_key)
	{
		i = 0;
		temp = *env_list;
		while (temp)
		{
			if (!ft_strncmp(temp -> content, *target_key, ft_strlen(*target_key)))
			{
				lst_rm(env_list, i);
				break ;
			}
			temp = temp -> next;
			i++;
		}
		target_key++;
	}
}
