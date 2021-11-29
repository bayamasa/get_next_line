/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:55:27 by mhirabay          #+#    #+#             */
/*   Updated: 2021/11/29 14:43:37 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*read_buffering(char **text, int *status, ssize_t text_len);
char	*get_next_line(int fd);
char	*store_buffer(	char *read_res, char **text, \
						int *status, ssize_t res_len);
char	*finish(char **text, char *read_res);
ssize_t	ft_strchr_index(const char *s, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *src);

#endif
