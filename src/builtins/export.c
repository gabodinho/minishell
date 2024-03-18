/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:12 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/18 16:57:29 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	contains_spaces(const char *str)
{
	while (*str)
	{
		if (*str == ' ')
			return (1);
		str++;
	}
	return (0);
}

char *ft_strnew(size_t size) {
    char *str = (char *)malloc((size + 1) * sizeof(char)); // Aloca memoria para la cadena más el carácter nulo
    if (!str) // Verifica si la asignación de memoria fue exitosa
        return NULL;
    for (size_t i = 0; i <= size; i++) // Inicializa todos los caracteres a '\0'
        str[i] = '\0';
    return str; // Devuelve el puntero a la cadena
}

void export_env_list(t_list **env_list, char *key, char *value) {
    if (!env_list || !key) // Verifica si los argumentos son nulos
        return;
    if (contains_spaces(key)) {
        perror("export: invalid identifier");
        return;
    }

    // Busca si la variable de entorno ya está presente en la lista
    t_list *current = *env_list;
    while (current) {
        char *env_entry = (char *)current->content;
        if (ft_strncmp(env_entry, key, ft_strlen(key)) == 0 && env_entry[ft_strlen(key)] == '=') {
            // Si la variable de entorno ya existe, actualiza su valor
            if (value) {
                char *new_entry = ft_strjoin(key, "=");
                if (!new_entry) {
                    perror("ft_strjoin");
                    return;
                }
                char *temp = new_entry;
                new_entry = ft_strjoin(new_entry, value);
                free(temp);
                if (!new_entry) {
                    perror("ft_strjoin");
                    return;
                }
                free(current->content); // Libera la memoria del contenido anterior
                current->content = new_entry; // Actualiza el contenido con el nuevo valor
            }
            return;
        }
        current = current->next;
    }

    // Si la variable de entorno no existe, la añade a la lista
    char *new_entry = NULL;
    if (value) {
        new_entry = ft_strjoin(key, "=");
        if (!new_entry) {
            perror("ft_strjoin");
            return;
        }
        char *temp = new_entry;
        new_entry = ft_strjoin(new_entry, value);
        free(temp);
        if (!new_entry) {
            perror("ft_strjoin");
            return;
        }
    } else {
        // Si no hay valor, simplemente añade la clave a la lista de entorno
        new_entry = ft_strdup(key);
        if (!new_entry) {
            perror("ft_strdup");
            return;
        }
    }
    ft_lstadd_back(env_list, ft_lstnew(new_entry));
}


void export_builtin(char **args, t_list **env_list) {
    if (!args || !*args) // Verifica si los argumentos son nulos o la lista de argumentos está vacía
        return;

    // Itera sobre los argumentos y para cada uno, verifica si es una asignación de variable de entorno
    for (int i = 0; args[i]; i++) {
        if (contains_spaces(args[i])) {
            printf("export: invalid identifier %s\n", args[i]);
            return;
        }

        char *equal_sign = ft_strchr(args[i], '=');
        if (equal_sign) {
            // Si se encuentra un signo igual, divide la cadena en la clave y el valor
            *equal_sign = '\0'; // Divide la cadena en la posición del signo igual
            char *key = args[i];
            char *value = equal_sign + 1;
            export_env_list(env_list, key, value + 1);
        } else {
            // Si no se encuentra un signo igual, verifica si el argumento es solo un signo igual
            if (ft_strcmp(args[i], "=") == 0) {
                printf("export: invalid format for argument %s\n", args[i]);
                return;
            }
        }
    }
}

