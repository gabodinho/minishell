/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:12 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/20 15:22:33 by irivero-         ###   ########.fr       */
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

void	export_env_list(t_list **env_list, char *key, char *value)
 {
	t_list	*current;
	char	*env_entry;
	char	*new_entry;
	char	*temp;
	
	if (!env_list || !key || contains_spaces(key) || (value && contains_spaces(value))) // Verifica si los argumentos son nulos
	{
		printf("export: invalid identifier %s\n", key);
		return ;
	}
	// Busca si la variable de entorno ya está presente en la lista
	current = *env_list;
	while (current) 
	{
		env_entry = (char *)current->content;
		if (ft_strncmp(env_entry, key, ft_strlen(key)) == 0 && env_entry[ft_strlen(key)] == '=')
		{
			// Si la variable de entorno ya existe, actualiza su valor
			if (value) 
			{
				new_entry = ft_strjoin(key, "=");
				if (!new_entry) 
				{
					perror("ft_strjoin");
					return ;
				}
				temp = new_entry;
				new_entry = ft_strjoin(new_entry, value);
				free(temp);
				if (!new_entry) 
				{
					perror("ft_strjoin");
					return;
				}
				//free(current->content); // Libera la memoria del contenido anterior
				current->content = new_entry; // Actualiza el contenido con el nuevo valor
			}
			return;
		}
		current = current->next;
	}

	// Si la variable de entorno no existe, la añade a la lista
	new_entry = NULL;
	if (value) 
	{
		new_entry = ft_strjoin(key, "=");
		if (!new_entry) 
		{
			perror("ft_strjoin");
			return ;
		}
		temp = new_entry;
		new_entry = ft_strjoin(new_entry, value);
		free(temp);
		if (!new_entry) 
		{
			perror("ft_strjoin");
			return ;
		}
	} 
	else 
	{
		// Si no hay valor, simplemente añade la clave a la lista de entorno
		new_entry = ft_strdup(key);
		if (!new_entry) 
		{
			perror("ft_strdup");
			return ;
		}
	}
	ft_lstadd_back(env_list, ft_lstnew(new_entry));
}

/*
void export_builtin(char **args, t_list **env_list) 
{
	char	*equal_sign;
	char	*key;
	char	*value;
	int		i;
	
	if (!args || !*args) // Verifica si los argumentos son nulos o la lista de argumentos está vacía
		return ;

	// Itera sobre los argumentos y para cada uno, verifica si es una asignación de variable de entorno
	i = 0;
	while (args[i]) 
	{
		if (contains_spaces(args[i])) {
			printf("export: invalid identifier %s\n", args[i]);
			return;
		}
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign) 
		{
			// Si se encuentra un signo igual, divide la cadena en la clave y el valor
			*equal_sign = '\0'; // Divide la cadena en la posición del signo igual
			key = args[i];
			value = equal_sign + 1;
			export_env_list(env_list, key, value);
		} 
		else 
		{
			// Si no se encuentra un signo igual, verifica si el argumento es solo un signo igual
			if (ft_strcmp(args[i], "=") == 0) 
			{
				printf("export: invalid format for argument %s\n", args[i]);
				return ;
			}
		}
		i++;
	}
}*/
/*
void export_builtin(char **args, t_list **env_list) 
{
    char    *equal_sign;
    char    *key;
    char    *value;
    int     i;
    
    if (!args || !*args) // Verifica si los argumentos son nulos o la lista de argumentos está vacía
        return ;

    // Itera sobre los argumentos y para cada uno, verifica si es una asignación de variable de entorno
    i = 0;
    while (args[i]) 
    {
        if (contains_spaces(args[i - 1])) {
            printf("export: invalid identifier %s\n", args[i]);
            return;
        }
        equal_sign = ft_strchr(args[i], '=');
        if (equal_sign) 
        {
            // Verificar si hay espacios en blanco antes del signo igual
            char *before_equal = args[i];
            while (before_equal < equal_sign && *before_equal == ' ')
                before_equal++;
            if (before_equal > equal_sign) 
            {
                printf("1\n");
                printf("export: invalid format for argument %s\n", args[i]);
                return;
            }
            
            // Si se encuentra un signo igual, divide la cadena en la clave y el valor
            *equal_sign = '\0'; // Divide la cadena en la posición del signo igual
            key = args[i];
            value = equal_sign + 1;
            export_env_list(env_list, key, value);
        } 
        else 
        {
            // Si no se encuentra un signo igual, verifica si el argumento es solo un signo igual
            if (ft_strcmp(args[i], "=") == 0) 
            {
                printf("export: invalid format for argument %s\n", args[i]);
                return ;
            }
            // Si no se encuentra un signo igual, solo exporta la
			export_env_list(env_list, args[i], NULL);
		}
		i++;
	}
}*/

void  print_export_error(char *var, char *val, char *message)
{

      ft_putstr_fd("bash: export: `", 2);
      ft_putstr_fd(var, 2);
      ft_putchar_fd('=', 2);
      ft_putstr_fd(val, 2);
      ft_putchar_fd('\'', 2);
      ft_putstr_fd(message, 2);
      ft_putstr_fd("\n", 2);
}

int is_valid_var_start(unsigned char c)
{
      if (ft_isalnum(c) || c == '_' || c != '=')
            return (1);
      else
            return (0);
}

int is_valid_var_char(char *var)
{
      int i = 0;

      while (var[i] != '\0')
      {
            if (!(ft_isalpha((unsigned char)var[i]) || var[i] == '_'))
                  return (0);
            i ++;
      }
      return (1);
}

char *remove_one_quote_set(char *str)
{
      size_t end;

      end = 0;
      end = ft_strlen(str) - 1;
      if (str[0] == '\'' && str[end] == '\'')
            str = ft_strtrim(str, "\'");
      else if (str[0] == '\"' && str[end] == '\"')
            str = ft_strtrim(str, "\"");
      return (str);
}

void	export_one_var(char **arr, t_list **env_list)
{
	char	*var;
	char	*val;
	char	*str;

	var = arr[0];
	val = arr[1];
	/* Si val es NULL, conviértelo en una cadena vacía */
	if (val == NULL)
		val = ft_strdup("");
	/* Unir la variable y el valor establecido */
	str = ft_strjoin(var, ft_strdup("="));
	str = ft_strjoin(str, val);
	/* Si var existe en env, elimínalo - unset */
	unset_env_list(env_list, var); // Suponiendo que tienes una función unset_one_var que elimina una variable de la lista env_list
	ft_lstadd_back(env_list, ft_lstnew(str));
}

int get_arg_count(char **argv)
{
	int len = 0;

	if (!argv)
		return (len);
	while (argv[len])
		len ++;
	return (len);
}

void free_arr(char **env, int len)
{
	int i = 0;

	while (i < len)
	{
		free(env[i]);
		env[i] = NULL;
		i ++;
	}
	free(env);
	env = NULL;
}

void	export_builtin(char **args, t_list **env_list)
{
	int		i = 1;
	char	**arr;

	arr = NULL;
	g_exit_status = 0;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '='))
		{
			arr = ft_split(args[i], '=');
			/* Eliminar las comillas " " y ' ' de var y val */
			if (arr[0])
				arr[0] = remove_one_quote_set(arr[0]);
			if (arr[1])
				arr[1] = remove_one_quote_set(arr[1]);
			/* Verificar los identificadores de var inválidos */
			if (!is_valid_var_start(arr[0][0]) || !is_valid_var_char(arr[0]))
			{
				g_exit_status = 1;
				print_export_error(arr[0], arr[1], " : not a valid identifier");
			}
			else
				export_one_var(arr, env_list);
			free_arr(arr, get_arg_count(arr));
		}
		i++;
	}
}
