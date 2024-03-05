/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:44:35 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/06/04 16:37:54 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
	return ;
}
/*
void print_lst(t_list *lst)
{
	t_list *ptr;

	ptr = lst;

	printf("This prints the entire list:\nfirst node: ");
	while (ptr -> next != 0)
	{
		printf("%s\n", (char *) ptr -> content);
		ptr = ptr -> next;
	}
	printf("last node: %s\n", (char *) ptr -> content);
	return ;
}

int main(void)
{
	t_list *new = ft_lstnew("A");
	t_list *second = ft_lstnew("B");
	new -> next = second;
	print_lst(new);
	t_list *third = ft_lstnew("C");
	ft_lstadd_front(&new, third);
	print_lst(third);
	return (1);
}
*/
