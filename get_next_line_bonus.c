/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:59:07 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/10 15:54:21 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_list	*create_or_find_fd_list(t_list *fd_list, int fd)
{
	while (fd_list != NULL)
	{
		if ((fd_list)->fd == fd)
			return (fd_list);
		fd_list = (fd_list)->next;
	}
	(fd_list) = (t_list *)malloc(sizeof(t_list));
	if (fd_list == NULL)
		return (NULL);
	(fd_list)->fd = fd;
	(fd_list)->buf = ft_strdup("\0");
	return ((fd_list));
}

char	*process_read_internal(char *tmp_str, t_list *tg_list)
{
	ssize_t	null_offset;
	ssize_t	lf_offset;
	char	*ret_str;

	lf_offset = ft_strchr_index(tmp_str, '\n');
	null_offset = ft_strchr_index(tmp_str, '\0');
	if (lf_offset != -1)
	{
		ret_str = ft_strjoin(tg_list->buf, \
			ft_substr(tmp_str, 0, lf_offset + 1));
		tg_list->buf = ft_substr(tmp_str, lf_offset + 1, null_offset);
		free(tmp_str);
		tmp_str = NULL;
		return (ret_str);
	}
	tg_list->buf = ft_strjoin(tg_list->buf, \
		ft_substr(tmp_str, 0, null_offset));
	free(tmp_str);
	tmp_str = NULL;
	return (NULL);
}

char	*process_read_done(char **tmp, \
	t_list **fd_list, t_list **tg_list)
{
	char	*ret_str;

	free(*tmp);
	if (*((*tg_list)->buf) != '\0')
	{
		ret_str = ft_strdup((*tg_list)->buf);
		free((*tg_list)->buf);
		(*tg_list)->buf = NULL;
		free(*fd_list);
		(*fd_list) = NULL;
		return (ret_str);
	}
	free((*tg_list)->buf);
	(*tg_list)->buf = NULL;
	free(*fd_list);
	*fd_list = NULL;
	return (NULL);
}

char	*process_read_before(t_list *tg_list)
{
	ssize_t			lf_offset;
	char			*ret_str;
	char			*tmp_str;

	lf_offset = ft_strchr_index(tg_list->buf, '\n');
	if (lf_offset != -1)
	{
		ret_str = ft_substr(tg_list->buf, 0, lf_offset + 1);
		tmp_str = ft_substr(tg_list->buf, lf_offset + 1, \
			 ft_strchr_index(tg_list->buf, '\0'));
		free(tg_list->buf);
		tg_list->buf = tmp_str;
		return (ret_str);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_list;
	t_list			*tg_list;
	char			*tmp_str;
	ssize_t			result;
	char			*ret_str;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	// アドレス値が固定されていないから毎回の呼び出しでアドレスが違うものが呼ばれてしまう。
	tg_list = create_or_find_fd_list(fd_list, fd);
	// printf("tg_list = %p\n", tg_list);
	ret_str = process_read_before(tg_list);
	if (ret_str)
		return (ret_str);
	while (1)
	{
		tmp_str = (char *)malloc(sizeof(char) * (ssize_t)BUFFER_SIZE + 1);
		if (tmp_str == NULL)
			return (NULL);
		result = read(fd, tmp_str, BUFFER_SIZE);
		if (result <= 0)
			return (process_read_done(&tmp_str, &fd_list, &tg_list));
		*(tmp_str + result) = '\0';
		ret_str = process_read_internal(tmp_str, tg_list);
		if (ret_str != NULL)
			return (ret_str);
	}
}
