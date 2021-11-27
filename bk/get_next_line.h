/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:12:13 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/28 13:38:14 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_list
{
	int				fd;
	char			*buf;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*create_or_find_fd_list(t_list **fd_list, int fd);
char	*process_read_internal(char *tmp_str, t_list *tg_list);
char	*process_read_done(char **tmp, t_list **fd_list, t_list **tg_list);
char	*process_read_before(t_list *tg_list);
size_t	ft_strlen(const char *str);
ssize_t	ft_strchr_index(const char *s, int c);
char	*ft_strdup(const char *src);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
