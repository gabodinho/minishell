/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:18:24 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/15 10:01:30 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "tokenizer.h"
# include "ft_printf.h"

void	append_token(t_token **token_lst, int type, char *str);
char	*get_environment_variable(char *name);
void	expand_environment_variables(t_token *token);
void	expand_exit_status(t_token *token);
t_token	*expand_tokens(char *line);

#endif