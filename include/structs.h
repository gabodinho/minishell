/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:25:38 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/11 21:41:33 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define GREEN "\033[38;5;10m"
# define RESET "\033[0m"
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_RESET   "\x1b[0m"

typedef enum e_ntype
{
	N_REDIR,
	N_HERE,
	N_PIPE,
	N_EXE
}	t_ntype;

typedef struct s_node
{
	t_ntype			ntype;
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*subnode;
	char			**param;
	struct s_list	*envir;
	char			*file;
	int				mode;
	int				fd;
	char			*delim;
}	t_node;

typedef struct s_data
{
	struct s_node	*tree;
	struct s_token	**tok_lst;
	struct s_list	**envir;
}	t_data;

typedef struct t_exp
{
	char			*str;
	int				quotes;
	struct t_exp	*next;
}	t_exp;

typedef struct s_string_info
{
	t_list	*env;
	int		exit_status;
}	t_string_info;

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

#endif
