/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:35:13 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/19 15:36:11 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_data	*get_data(t_token **toklst, t_list **envir, t_node *tree)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data -> tree = tree;
	data -> envir = envir;
	data -> tok_lst = toklst;
	return (data);
}
