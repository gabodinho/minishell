/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_extension.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:04:19 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/10 14:13:22 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "ft_printf.h"

int	find_end_delim(char *str, char c)
{
	int	i;

	if (!*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (c && str[i] == c)
			return (i);
		else if (!c && ft_strchr("\'\"", str[i]))
			return (i);
		i++;
	}
	if (!c)
		return (i);
	else
		return (-1);
}

t_exp	*split_quotes(char *str)
{
	t_exp	*exp;
	int		end;
	char	*word;

	exp = 0;
	while (*str)
	{
		if (ft_strchr("\'\"", *str))
		{	
			end = find_end_delim(str + 1, *str);
			word = ft_substr(str + 1, 0, end);
			exp_append(&exp, word, *str);
			str += end + 2;
		}
		else
		{
			end = find_end_delim(str, 0);
			word = ft_substr(str, 0, end);
			exp_append(&exp, word, 0);
			str += end;
		}
		if (end == -1)
			printf("split_quotes error");
	}
	return (exp);
}

/*
int	main(void)
{
	t_exp *new;
	t_exp *ptr;
	
	char *str = "this\'is\"\'\"a_test\"_\'end\'";
	printf("%s\n", str);
	new = split_quotes(str);
	ptr = new;

	while (new)
	{
		printf("%s + param: %d\n", new -> str, new -> quotes);
		new = new -> next;
	}
	clear_exp(&ptr);
	while (ptr)
	{
		printf("%s + param: %d\n", new -> str, new -> quotes);
		new = new -> next;
	}
	printf("end");
	return (0);
}
*/
