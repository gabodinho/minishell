/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:18:24 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/06 01:13:47 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "structs.h"
# include "parser.h"
# include "tokenizer.h"
# include "ft_printf.h"

int		is_envirom(char *str, int i);
int		is_env_char(char c);
int		is_token_in_env(char *str);
int		find_dollar(char *str, int i);
void	new_string(char *new_str, char *subs1, char *value, char *subs2);
char	*create_string(t_list *env, char *token, int start_d, int end_d, int exit_status);

char 	*get_env_value(t_list *env,  char *env_key);

void	expander(t_list *env, t_token *token, int exit_status);
void	clear_exp(t_exp **exp);
t_exp	*split_quotes(char *str);


#endif
