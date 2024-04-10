/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:37:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 09:44:32 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"


void	handle_eof_error(t_token **token_lst, char *line, t_list *envir)
{
	free(line);
	clear_list(token_lst);
	ft_lstclear(&envir, free);
	printf("minishell: syntax error: unexpected EOF\nexit\n");
	exit(2);
}
