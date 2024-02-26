/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:18:20 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/26 12:22:28 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

bool	skip_quotes(char *line, size_t  *i)
{
	char	quote;
	char	*end_quote;

	quote = line[*i];
	end_quote = ft_strchr(line + *i + 1, quote);
	if (end_quote != NULL)
	{
		//(*i) += 1 + (end_quote - (line + *i + 1));
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}
/*
int main()
{
    char test_line[] = "This 'is a' a test \"string\" for the skip_quotes function.";
    size_t i = 0;

    while (test_line[i] != '\0')
    {
        if (is_quotes(test_line[i]))
        {
            if (skip_quotes(test_line, &i))
            {
                printf("SKIPPED QUOTES\n");
            }
            else
            {
                printf("Error: Missing closing quote.\n");
                break;
            }
        }
        else
        {
            printf("Current character: %c\n", test_line[i]);
            i++;
        }
    }

    return 0;
}*/
/*
// check if a string is one of the predefined redirection symbols.
// returns 1 if it is, 0 otherwise
int	is_redirections(const char *str)
{
	const char	*redir[] = {"<<", "<", ">", ">>"}; 
	int			i;

	if (str == NULL)
		return (0);
	i = 0;
	while (i < sizeof(redir) / sizeof(redir[0]))
	{
		if (ft_strcmp(str, redir[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

//find the end of a quoted string starting from index 'i'.
// update the type of the quote(single or double)
// return the index of the closing quote string or -1 if the end is not found.
int	find_quotes(const char *line, int i, char quote_char)
{
	while (line[i] != quote_char && line[i] != '\0')
	{
		if (line[i] == '\\' && line[i + 1] == quote_char)
			i++;
		i++;
	}
	if (line[i] == '\0')
		return (-1);
	else
		return (i);
}

// Find the end of a single quote string starting from index 'i'.
// return the index of the closing quote string or -1 if the end is not found.
int	single_quotes(const char *line, int i)
{
	int	res;

	res = find_quotes(line, i + 1, '\'');
	return (res);
}

// Find the end of a double quote string starting from index 'i'.
// return the index of the closing quote string or -1 if the end is not found.
int	double_quotes(const char *line, int i)
{
	int	res;

	res = find_quotes(line, i + 1, '\"');
	return (res);
}

// Find the end of a quoted string starting from index 'i' and update the token type.
// return the index of the closing quote string or -1 if the end is not found.
// also, updates the type of the token if it's not NULL.
int	quotes_end(const char *line, int i, t_token *token)
{
	char	quote_char;
	int		res;
	
	quote_char = line[i];
	res = find_quotes(line, i + 1, quote_char);
	if (line[i + 1] == '\0')
		return (-1);
	if (token != NULL)
	{
		if (quote_char == '\'')
			token->type = SINGLE_QUOTES;
		else
			token->type = DOUBLE_QUOTES;
	}
	return (res);
}

void	assign_token_types(t_itokens *itokens)
{
	int	cur_index;

	cur_index = 0;
	itokens->token[itokens->size].type = T_NULL;
	while (cur_index < itokens->size)
	{
		if (!ft_strcmp(itokens->token[cur_index].str, "|"))
			itokens->token[cur_index].type = PIPE;
		else if (is_redirections(itokens->token[cur_index].str))
			itokens->token[cur_index].type = REDIR;
		else
			itokens->token[cur_index].type = WORD;
		cur_index++;
	}
}*/