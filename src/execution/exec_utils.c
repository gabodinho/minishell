/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:32:59 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/11 02:33:06 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "execution.h"
#include "builtins.h"

int	is_path(char *str)
{
	if (str[0] == '/' || str[0] == '.')
		return (1);
	return (0);
}

void	reset_stdin(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_RDONLY);
	dup2(tty_fd, STDIN_FILENO);
	close(tty_fd);
}

void	reset_stdout(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_WRONLY);
	dup2(tty_fd, STDOUT_FILENO);
	close(tty_fd);
}

char	*find_exec(char *exec_file, char *path_var)
{
	char	**vars;
	char	**ptr;
	char	*temp;
	char	*temp2;

	if (!path_var)
		return (NULL);
	vars = ft_split(path_var, ':');
	ptr = vars;
	while (*vars)
	{
		temp = ft_strjoin(*vars, "/");
		temp2 = ft_strjoin(temp, exec_file);
		free(temp);
		if (!access(temp2, F_OK))
			return (temp2);
		free(temp2);
		vars++;
	}
	del_arr(ptr);
	return (NULL);
}

int	is_builtin_exec(t_node *tree)
{
	if (tree -> ntype == N_PIPE)
		return (1);
	while (tree -> ntype != N_EXE)
		tree = tree -> subnode;
	if (is_builtin(tree -> param[0]))
		return (0);
	else
		return (1);
}
