/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:37:44 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/10 10:04:07 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "builtins.h"

void	handle_eof_error(t_token **token_lst, char *line, t_list *envir)
{
	free(line);
	clear_list(token_lst);
	ft_lstclear(&envir, free);
	rl_clear_history();
	printf("minishell: syntax error: unexpected EOF\nexit\n");
	exit(2);
}

void	exit_with_cleaup(t_data *data, int exit_status)
{
	clear_list(data->tok_lst);
	ft_lstclear(data->envir, free);
	clear_tree(data->tree);
	free(data);
	rl_clear_history();
	exit(exit_status);
}
