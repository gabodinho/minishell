/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:39:49 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/15 10:25:45 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "expander.h"

#define MAX_TOKEN_LENGTH 100

void	append_token(t_token **token_lst, int type, char *str) 
{
	t_token *new_token;
	t_token *current;
	
	new_token = create_token(str, type);
	if (*token_lst == NULL) 
	{
		*token_lst = new_token;
	} 
	else 
	{
		current = *token_lst;
		while (current->next != NULL) 
		{
			current = current->next;
		}
		current->next = new_token;
		new_token->prev = current;
	}
}

char	*get_environment_variable(char *name) 
{
	return getenv(name);
}

void	expand_environment_variables(t_token *token) 
{
	char	*start;
	char	*end;
	size_t	var_name_length;
	char	var_name[MAX_TOKEN_LENGTH];
	char	*value;
	
	start = strchr(token->str, '$');
	if (start != NULL) {
		end = start + 1;
		while (*end && !is_space(*end)) 
		{
			end++;
		}
		var_name_length = end - start - 1;
		strncpy(var_name, start + 1, var_name_length);
		var_name[var_name_length] = '\0';
		value = get_environment_variable(var_name);
		if (value != NULL) 
		{
			free(token->str); // Liberamos la cadena actual
			token->str = ft_strdup(value); // Asignamos la nueva cadena
		}
	}
}

void	expand_exit_status(t_token *token) 
{
	char *start;
	char exit_status_str[MAX_TOKEN_LENGTH];
	
	start = strstr(token->str, "$?");
	if (start != NULL) 
	{
		sprintf(exit_status_str, "%d", errno); // errno holds the exit status
		ft_memmove(start, exit_status_str, ft_strlen(exit_status_str));
		ft_memmove(start + ft_strlen(exit_status_str), start + 2, ft_strlen(start + 2) + 1);
	}
}

t_token	*expand_tokens(char *line) 
{
	t_token *token_lst;
	t_token *current;
	char	*token;
	
	token_lst = NULL;
	token = strtok(line, " ");
	while (token != NULL) 
	{
		append_token(&token_lst, 0, token); // Aquí el tipo de token es 0 por defecto
		token = strtok(NULL, " ");
	}

	// Expandir variables de entorno y estado de salida
	current = token_lst;
	while (current != NULL) 
	{
		expand_environment_variables(current);
		expand_exit_status(current);
		current = current->next;
	}

	return token_lst;
}
/*
int	main() 
{
	char line[] = "ls -l $HOME $?";
	t_token *expanded_tokens = expand_tokens(line);
	print_token_list(expanded_tokens);
	free_tokens(expanded_tokens);
	return 0;
}
*/
