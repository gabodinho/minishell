/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:42:14 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/02 21:01:53 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

size_t	gnl_strlen(const char *str);
size_t	gnl_strlcpy(char *dst, const char *src, size_t size);
int		get_idx(char *str);
char	*shift_previous(char *previous);
char	*get_linee(char *previous);
void	gnl_concat(char *dst, char *prefix, char *sufix);
char	*get_buf(char *previous, int *bytswrtn, int fd);
char	*get_next_line(int fd);

#endif
