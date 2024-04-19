/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:32:25 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/16 14:11:38 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "signals.h"
#include "parser.h"
#include "builtins.h"

void	run_exec(t_node *node, t_data *data)
{
	char	*path;
	char	**env_arr;

	if (!node -> param[0])
		return ;
	env_arr = conv_env(*(data -> envir));
	path = NULL;
	if (is_builtin(node -> param[0]))
		return (exec_builtins(node -> param, data), (void) 0);
	if (is_path(node -> param[0], env_arr, data))
		path = ft_strdup(node -> param[0]);
	else
		path = find_exec(node-> param[0], search_env("PATH", *(data-> envir)));
	if (path)
		execve(path, node -> param, env_arr);
	del_arr(env_arr);
	free(path);
	perror(node -> param[0]);
	exit_with_cleaup(data, 127);
}
