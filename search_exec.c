/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:12:05 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/03/14 18:13:02 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*find_exec(char *exec_file, char *path_var)
{
	char	**vars;
	char	*temp;

	if (!path_var)
		return (NULL);
	vars = ft_split(path_var, ':');
	while (vars)
	{
		temp = ft_strjoin(*vars, exec_file);
		if (!access(temp, F_OK))
			return (temp);
		free(temp);
		vars++;
	}
//	free(vars)	?
	return (NULL);
}

/*
void	run_builtin(char **cmd, t_list *envir)
{
	if (!strncmp(cmd[0], "export"))
		ft_export(cmd);
	else if (!strncmp(cmd[0], "pwd")
		ft_pwd(envir);
	else if (!strncmp(cmd[0], "unset")
		ft_unset(cmd, envir);
	else if (!strncmp(cmd[0], "env")
		ft_env(envir);
	else if (!strncmp(cmd[0], "exit")
		ft_exit();
	else if (!strncmp(cmd[0], "echo")
		ft_echo(cmd);
	return ;
}
*/

