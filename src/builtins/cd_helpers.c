/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:55:46 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/02 09:58:05 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Función para cambiar el directorio actual
char	*change_directory(char *new_dir)
{
	if (chdir(new_dir) == -1)
	{
		perror("chdir");
		return (NULL);
	}
	return (getcwd(NULL, 0));
}
