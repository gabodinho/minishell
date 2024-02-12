/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:53:04 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/12 15:53:08 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char    *path_finder(char **env)
{
        int     i;

        i = 0;
        while (env[i] != NULL)
        {
                if (f_strcmp("HOME=", env[i]) == 0)
                        break ;
                i++;
        }
        return (env[i]);
}

char    *path_to_usr(char *path)
{
        int     i;

        i = 0;
        while (path[i] != '/')
                i++;
        return (path + i);
}

char    *path_filler(char **paths, t_envp *env, char *path)
{
        char    *tmp;

        path = path_finder(env->envp);
        path = path_to_usr(path);
        if (paths[1] && paths[1][0] == '~')
        {
                tmp = malloc(f_strlen(path) + f_strlen(paths[1]) + 1);
                ft_strlcpy(tmp, path, f_strlen(path) + 1);
                ft_strlcat(tmp, paths[1] + 1, f_strlen(tmp) + f_strlen(paths[1]) + 1);
                path = tmp;
        }
        return (path);
}

char    *f_strlcpy(char *src)
{
        int             j;
        char    *tmp;

        if (!src)
                return (NULL);
        tmp = malloc(f_strlen(src) + 1);
        j = 0;
        while (src && src[j])
        {
                tmp[j] = src[j];
                j++;
        }
        tmp[j] = '\0';
        free(src);
        return (tmp);
}

void    change_directory(char **paths, t_envp *env)
{
        char    *path;
        char    *ptr[2];

        ptr[0] = "1";
        ptr[1] = NULL;
        path = NULL;
        if (env->cd_hist != NULL && (paths[1] && \
        ft_strcmp(paths[1], "-") == 0) && paths[2] == NULL)
                path = env->cd_hist;
        else if (paths[1])
                path = paths[1];
        if (!env->cd_hist)
                env->cd_hist = f_strlcpy(our_pwd(ptr, 0));
        if (!path || f_strcmp(path, "~") == 0)
                path = path_filler(paths, env, path);
        if (chdir(path) == -1)
        {
                g_exit_status = 1;
                printf("cd: no such file or directory: %s\n", path);
                return ;
        }
        g_exit_status = 0;
}