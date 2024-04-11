/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:25:38 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/11 13:49:51 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
