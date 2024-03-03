/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:44:35 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/06/04 16:25:22 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst -> content);
	free(lst);
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
		if (ptr -> content)
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
	ft_lstdelone(second, free);
	t_list *third = ft_lstnew("C");
	ft_lstadd_front(&new, third);
	print_lst(new);
	printf("last node content is: %s", (char *) ft_lstlast(third) -> content);
	return (1);
}
*/
