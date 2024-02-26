/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:59:14 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/26 14:48:38 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Función para extraer una subcadena de una cadena dada
char *ft_substr(char *s, unsigned int start, size_t len) {
    if (!s)
        return NULL;

    size_t s_len = 0;
    while (s[s_len])
        s_len++;

    if (start >= s_len)
        return NULL;

    len = (len < s_len - start) ? len : s_len - start;

    char *substr = (char *)malloc((len + 1) * sizeof(char));
    if (!substr)
        return NULL;

    for (size_t i = 0; i < len; i++)
        substr[i] = s[start + i];

    substr[len] = '\0';
    return substr;
}

// Función para comparar los primeros n caracteres de dos cadenas
int ft_strncmp(char *s1, char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i])
            return (int)(unsigned char)s1[i] - (int)(unsigned char)s2[i];
        if (s1[i] == '\0')
            return 0;  // Ambas cadenas son iguales hasta el final de la cadena más corta
    }
    return 0;  // Las primeras n caracteres son iguales
}

// Función para buscar la primera aparición de un carácter en una cadena
char *ft_strchr(char *s, int c) {
    while (*s != (char)c) {
        if (*s == '\0')
            return NULL;  // Carácter no encontrado
        s++;
    }
    return (char *)s;  // Devuelve un puntero al primer carácter encontrado
}

void *ft_calloc(size_t count, size_t size) 
{
    void *ptr = malloc(count * size);

    if (ptr != NULL) {
        // Inicializa la memoria a cero
        for (size_t i = 0; i < count * size; ++i) {
            ((char *)ptr)[i] = 0;
        }
    }

    return ptr;
}

char *ft_strdup(const char *str) 
{
    size_t len = strlen(str) + 1; // Longitud de la cadena, incluyendo el carácter nulo
    char *duplicate = (char *)malloc(len);

    if (duplicate != NULL) {
        strcpy(duplicate, str); // Copia la cadena original en la nueva memoria asignada
    }

    return duplicate;
}
