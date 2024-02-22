/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:58:15 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/19 13:25:23 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// need function to count the tokens and also to find the end of the tokens
// maybe find the tokens and put them in an array with individual token strings
// take into account the quotes and spaces
// function to iterate through the characters of the line

// Cuenta el tamanho de un token en la string
// str: cadena de texto a analizar
// i: puntero a la posicion actual en la cadena
// size: puntero al contador de tokens
void	count_tokens(char *str, int *i, int *size)
{
	int		quote;

	while (is_space(str[*i]))
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = quotes_end(str, *i, NULL);
		if (quote != -1)
		{
			*i = quote + 1;
			(*size)++;
		}
	}
	else
	{
		while (str[*i] != '\0' && !is_space(str[*i]) && str[*i] != '\''
			&& str[*i] != '\"')
			(*i)++;
		(*size)++;
	}
}

// Cuenta el numero total de tokens simplificadamente en una cadena de texto
// str: cadena de texto a analizar
// return: el tamanho total de tokens
int	counter_simplified(char *str)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		count_tokens(str, &i, &size);
		if (i == -1)
			printf("Error\nCounting tokens\n");
	}
	return (size);
}

// Procesa un solo carácter en la cadena y construye tokens
// i: puntero a la posicion actual en la cadena
// str: cadena de texto a analizar
// token: puntero al array de tokens a construir
// token_idx: puntero al indice actual en el array de token
void	process_token_char(int *i, const char *str, t_token *token, int *token_idx)
{
	int	quote;
	if (is_space(str[*i]))
		(*i)++;
	else if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = *i;
		*i = quotes_end(str, *i, &token[*token_idx]);
		if (*i == -1)
			return ;
		token[(*token_idx)++].str = ft_substr(str, quote + 1, *i - quote - 1);
		(*i)++;
	}
	else
	{
		quote = *i;
		while (str[*i] && !is_space(str[*i]) && !(str[*i] == '\'' || str[*i] == '\"'))
			(*i)++;
		token[(*token_idx)++].str = ft_substr(str, quote, *i - quote);
	}
}

// Tokeniza la cadena de texto y construye un array de tokens
// str: cadena de texto a analizar
// token: puntero al array de tokens a construir
// max: el tamanho maximo del array de tokens
// return: puntero al array de tokens construido
t_token	*tokenize_and_build_array(const char *str, t_token *token, int max)
{
	int		i;
	int		row;
	
	i = 0;
	row = 0;
	while (str[i] && row < max)
		process_token_char(&i, str, token, &row);
	token[row].str = NULL;
	return (token);
}

// Divide la cadena en tokens utilizando la funcion tokenize_and_build_array
// str: cadena de texto a analizar
// itokens: estructura que tiene un array de tokens y el tamaño
// devuelve 0 si tiene éxito y -1 si hay un error
int	split_token(char *str, t_itokens *itokens)
{
	if (*str == '\0')
		return (-1);
	itokens->size = counter_simplified(str);
	if (itokens->size <= 0)
		return (-1);
	itokens->token = (t_token *)malloc(sizeof(t_token) * itokens->size + 1);
	if (itokens->token == NULL)
		return (-1);
	itokens->token = tokenize_and_build_array(str, itokens->token, itokens->size);
	return (0);
}

/*
int main() 
{
    char *input_str = "Hello 'World' \"This is a string\" >> | >>";
    t_itokens itokens;

    if (split_token(input_str, &itokens) != 0) 
	{
        fprintf(stderr, "Error al dividir tokens.\n");
        return 1;
    }
    for (int i = 0; i < itokens.size; i++)
		printf("Token %d: '%s'\n", i + 1, itokens.token[i].str);
    free_tokens(&itokens);
	return (0);
}*/
/*

int	main() 
{
    const char *input_str = "Hello  'World' \"This  is a string\" < >>";
    t_token tokens[10];  // Suponiendo un máximo de 10 tokens
    int index = 0;
    int i = 0;
    //while (input_str[i] != '\0') 
    //    process_token_char(&i, input_str, tokens, &index);
    //for (int j = 0; j < index; j++)
    //    printf("Token %d: '%s'\n", j + 1, tokens[j].str);
	tokenize_and_build_array(input_str, tokens, 10);
	for(int k = 0; tokens[k].str != NULL; k++)
		printf("Token %d: %s\n", k + 1, tokens[k].str);
	//free_tokens(&itokens);
    return (0);
}
*/
/*
int main()
{
    char *str = "This 'is a' test \"string\" for the tokenizer function.";
    int i = 0;
    int size = counter_simplified(str);
;
    //while (str[i] != '\0')
     //   count_tokens(str, &i, &size);
	printf("string: %s\n", str);
    //printf("size with the first function: %d\n", size);
	//while (str[i] != '\0')
	printf("counter function: %d\n", size);
    return (0);
}*/