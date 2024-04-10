
#include "signals.h"
#include "execution.h"
#include "builtins.h"

void	run_redir(t_node *node, t_data *data, int is_builtin)
{
	int	new_fd;

	if (node -> fd == STDIN_FILENO)
		reset_stdin();
	else if (node -> fd == STDOUT_FILENO)
		reset_stdout();
	new_fd = open(node->file, node->mode, 0666);
	if (new_fd < 0 && !is_builtin)
		panic(node->file);
	else if (new_fd < 0 && is_builtin)
	{
		g_signal = 2020;	// abort builtin execution
		printf("%s: No such file or directory\n", node -> file);
			return ;
	}
	dup2(new_fd, node -> fd);
	close(new_fd);
	if (!is_builtin)
		run_tree(node -> subnode, data);
	else
		return ;
}
