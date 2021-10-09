/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:08:45 by tisoya            #+#    #+#             */
/*   Updated: 2021/09/20 14:57:24 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# ifndef FD_MAX
#  define FD_MAX OPEN_MAX
# endif

char		*get_next_line(int fd);
void		ft_gnl_free(char **p1, char **p2);
void		ft_gnl_strmove(char *line, size_t len);
char		*ft_gnl_trim_until_end(char **line, ssize_t rc);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *src);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin_gnl(char *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

#endif
