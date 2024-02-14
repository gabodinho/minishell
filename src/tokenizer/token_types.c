/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:18:20 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/14 14:51:46 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

//check if a character is a space
int is_space(char c)
{
	if (c == ' ')
		return (1);
	else
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
	int res;

	res = find_quotes(line, i + 1, '\'');
	return (res);
}

// Find the end of a double quote string starting from index 'i'.
// return the index of the closing quote string or -1 if the end is not found.
int double_quotes(const char *line, int i)
{
	int res;
	
	res = find_quotes(line, i + 1, '\"');
	return (res);
}

// Find the end of a quoted string starting from index 'i' and update the token type.
// return the index of the closing quote string or -1 if the end is not found.
// also, updates the type of the token if it's not NULL.
int quotes_end(const char *line, int i, t_token *token)
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
	int cur_index;

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
}

/*
int main()
{
    const char *test_str = ">";
    if (is_redirections(test_str))
        printf("%s is a redirection\n", test_str);
    else
        printf("%s is not a redirection\n", test_str);
    return (0);
}
*/
/*
int main() 
{
    const char *test_line = "This is 'a single-quoted' and \"a double-quoted\" string.";
	
    int single_quotes_pos = single_quotes(test_line, 1);
    int double_quotes_pos = double_quotes(test_line, 1);
    printf("Single quotes position: %d\n", single_quotes_pos);
    printf("Double quotes position: %d\n", double_quotes_pos);
    // Test for find_quotes_to_end
    t_token token;
    int single_quotes_end = quotes_end(test_line, 9, &token);
    printf("Single quotes end position: %d\n", single_quotes_end);
    int double_quotes_end = quotes_end(test_line, 32, &token);
    printf("Double quotes end position: %d\n", double_quotes_end);
    return (0);
}*/