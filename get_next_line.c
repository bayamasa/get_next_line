/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:59:07 by mhirabay          #+#    #+#             */
/*   Updated: 2021/11/07 20:40:02 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*create_or_find_fd_list(t_list **fd_list, int fd)
{
	while ((*fd_list))
	{
		if ((*fd_list)->fd == fd)
			return (*fd_list);
		if (!((*fd_list)->next))
			(*fd_list) = (*fd_list)->next;
	}
	(*fd_list) = (t_list *)malloc(sizeof(t_list));
	if (*fd_list == NULL)
		return (NULL);
	(*fd_list)->fd = fd;
	(*fd_list)->buf = ft_strdup("\0");
	if ((*fd_list)->buf == NULL)
	{
		free(*fd_list);
		*fd_list = NULL;
		return (NULL);
	}
	return ((*fd_list));
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
		if (!ret_str)
			free(tg_list->buf);
		// ここがnullだとセグフォ
		tg_list->buf = ft_substr(tmp_str, lf_offset + 1, null_offset);
		free(tmp_str);
		tmp_str = NULL;
		return (ret_str);
	}
	// ここがnullだとセグフォ
	tg_list->buf = ft_strjoin(tg_list->buf, \
		ft_substr(tmp_str, 0, null_offset));
	free(tmp_str);
	tmp_str = NULL;
	return (NULL);
}

char	*process_read_done(char **tmp, t_list **fd_list, t_list **tg_list)
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
		// ここがnullでもセグフォ
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
	tg_list = create_or_find_fd_list(&fd_list, fd);
	if (tg_list == NULL)
		return (NULL);
	ret_str = process_read_before(tg_list);
	while (1)
	{
		if (ret_str)
			return (ret_str);
		tmp_str = (char *)malloc(sizeof(char) * (ssize_t)BUFFER_SIZE + 1);
		if (tmp_str == NULL)
			return (NULL);
		result = read(fd, tmp_str, BUFFER_SIZE);
		if (result <= 0)
			return (process_read_done(&tmp_str, &fd_list, &tg_list));
		*(tmp_str + result) = '\0';
		ret_str = process_read_internal(tmp_str, tg_list);
	}
}
