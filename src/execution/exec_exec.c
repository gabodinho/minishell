
#include "execution.h"
#include "signals.h"
#include "parser.h"
#include "builtins.h"

void	run_exec(t_node *node, t_data *data)
{
	char	*path_to_exec;
	char	*env_str;
	char	**env_arr;

	env_arr = conv_env(*(data -> envir));
	path_to_exec = NULL;
	if (!node -> param[0])
		return ;
	if (is_builtin(node -> param[0]))
		return (exec_builtins(node -> param, data), (void) 0);
	if (is_path(node -> param[0]))
		path_to_exec = ft_strdup(node -> param[0]);
	else
	{
		env_str = search_env("PATH", *(data -> envir));
		path_to_exec = find_exec(node -> param[0], env_str);
	}
	if (path_to_exec)
		execve(path_to_exec, node -> param, env_arr);
	del_arr(env_arr);
	free(path_to_exec);
	panic(node -> param[0]);
}
