/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_extension.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:04:19 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/05 00:59:51 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "ft_printf.h"

static void	clear_exp_recu(t_exp *exp)
{
	if (exp -> next)
		clear_exp_recu(exp -> next);
	free(exp -> str);
	free(exp);
}

void	clear_exp(t_exp **exp)
{
	if (!*exp)
		return ;
	clear_exp_recu(*exp);
	*exp = 0;
}

t_exp	*new_exp(char *str, int quotes)
{
	t_exp	*new;

	new = malloc(sizeof(t_exp));
	if (!new)
		return (perror("new_exp: malloc"), NULL);
	new -> str = str;
	new -> quotes = quotes;
	new -> next = NULL;
	return (new);
}

void	exp_append(t_exp **start, char *str, int quotes)
{
	t_exp	*ptr;

	ptr = *start;
	if (!ptr)
	{
		*start = new_exp(str, quotes);
		return ;
	}
	while (ptr && ptr -> next)
		ptr = ptr -> next;
	ptr -> next = new_exp(str, quotes);
}

// assuming unclosed qoutes were already dealt with in tokenizer
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
