/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:15:32 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/12 16:05:32 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

/* Main Functions */
char	*get_next_line(int fd);
char	*read_file(int fd, char *buffer);
char	*next_line(char *buffer);
char	*leftover(char *buffer);

/* Helper Functions*/
char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
size_t	gnl_strlen(char *str);

#endif