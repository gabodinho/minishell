/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:49:31 by irivero-          #+#    #+#             */
/*   Updated: 2024/03/12 10:12:17 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
//#include "../../libft/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

int g_exit_status = 0;
extern char **environ;

// Función para cargar las variables de entorno en una estructura t_envp
t_envp *load_env() {
    t_envp *env = malloc(sizeof(t_envp));
    
    // Inicializa env->envp con una copia de la variable global environ
    char **env_var = environ;
    int count = 0;

    // Cuenta la cantidad de variables de entorno
    while (*env_var != NULL) {
        count++;
        env_var++;
    }

    // Asigna memoria para la matriz envp
    env->envp = malloc((count + 1) * sizeof(char *));
    
    // Copia las variables de entorno a env->envp
    for (int i = 0; i < count; i++) {
        env->envp[i] = strdup(environ[i]);
    }

    // Agrega NULL al final de la matriz
    env->envp[count] = NULL;

    // Otras inicializaciones según sea necesario
    env->cd_hist = NULL;

    return env;
}

// Función para liberar la memoria de la estructura t_envp
void free_env(t_envp *env) {
    // Libera las variables de entorno
    char **env_var = env->envp;
    while (*env_var != NULL) {
        free(*env_var);
        env_var++;
    }

    // Libera la matriz envp y la estructura t_envp
    free(env->envp);
    free(env);
}

// Función para ejecutar el comando correspondiente
void execute_command(char **args, t_envp *env) {
    if (args[0] == NULL) {
        // No hay comando, simplemente presionaron Enter
        return;
    }

    if (strcmp(args[0], "exit") == 0)
        exit_command(args);
	else if (strcmp(args[0], "unset") == 0)
		ft_unset(args[1], env);
	else if (strcmp(args[0], "export") == 0)
		export(args, env);
    else if (strcmp(args[0], "echo") == 0)
        our_echo(args);
    else if (strcmp(args[0], "pwd") == 0)
        our_pwd(args, 0);
    else if (strcmp(args[0], "env") == 0)
        ft_env(env);
    else if (strcmp(args[0], "cd") == 0)
        change_directory(args, env);
    else 
	{
        // Comando desconocido
        printf("minishell: command not found: %s\n", args[0]);
    }
}

int main(void) {
    char *input;
    t_envp *env = load_env();

    while (1) {
        input = readline("minishell> ");
        if (!input) {
            // Handle EOF or error
            break;
        }

        char *args[64];
        int i = 0;
        char *token = strtok(input, " ");
        while (token && i < 64 - 1) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Ejecutar el comando correspondiente
        execute_command(args, env);
		printf("exit status: %d\n", g_exit_status);
        add_history(input);
        free(input);
    }

    // Liberar memoria antes de salir
    free_env(env);

    return 0;
}
