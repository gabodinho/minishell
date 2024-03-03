#ifndef GENERATED_HEADER_H
#define GENERATED_HEADER_H

#include "parser.h"
void    *heredoc_cmd(t_token *token);
void	*redir_cmd(t_token *token);
t_pipecmd	*pipe_cmd(t_token **left_list, t_token **right_list);
void    *parse_redir(void *cmd, t_token **toklist);
t_execmd	*init_execmd(void);
void	add_attribute(t_execmd *node, char *str);
void	*parse_exe(t_token **toklist);
void	*parse_pipe(t_token **toklist);

#endif // GENERATED_HEADER_H
