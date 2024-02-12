/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:18:20 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/12 14:48:56 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirections(char *str)
{
	
}

int is_space(char c)
{
	if (c == ' ')
		return (1);
	else
		return (0);

}

/*find end index of single quote string in the input line. 
returns the index of the ending */
int	single_quotes()
{

}

/*similar functionality*/
int	double_quotes()
{

}

/*find the end of a quoted string and update the type*/
int	find_quotes()
{

}
