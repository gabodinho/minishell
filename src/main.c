/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:12:59 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/12 15:21:31 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// including the flag --lreadline to work!
int	main()
{
	char *input;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("error al leer");
			break;
		}
		if (*input)
		{
			add_history(input);
			printf("entrada recibida: %s\n", input);
		}
		free(input);
	}
	return (0);
}