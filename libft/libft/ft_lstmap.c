/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:44:35 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/06/04 16:23:52 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	void	*content;

	start = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		content = f(lst -> content);
		if (!content)
		{
			ft_lstclear(&start, del);
			return (0);
		}
		ft_lstadd_back(&start, ft_lstnew(content));
		lst = lst -> next;
	}
	ft_lstlast(start)-> next = 0;
	return (start);
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
	t_list *fourth = ft_lstnew("D");
	ft_lstadd_back(&new, fourth);
	print_lst(third);
	return (1);
}
*/
