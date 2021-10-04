/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:59:07 by mhirabay          #+#    #+#             */
/*   Updated: 2021/10/04 17:17:21 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*create_or_find_fd_list(t_list **fd_list, int fd)
{
	//既にあるリソースからfdを探してくる
	while (*fd_list)
	{
		// fdが見つかった場合はfdを返す
		if ((*fd_list)->fd == fd)
			return (*fd_list);
		// nextが存在しない場合は、nextを現在のアドレスにする。
		// そんでwhileでループが終了することによってmallocが発動する。
		if(!((*fd_list)->next))
			(*fd_list) = (*fd_list)->next;
	}
	(*fd_list) = (t_list *)malloc(sizeof(t_list));
	if(*fd_list == NULL)
		return (NULL);
	(*fd_list)->fd = fd;
	(*fd_list)->buf = ft_strdup("\0");
	return ((*fd_list));
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dsize;
	size_t	ssize;
	size_t	total_size;
	size_t	i;
	size_t	condition;

	dsize = ft_strlen((char *)dest);
	ssize = ft_strlen((char *)src);
	total_size = dsize + ssize;
	condition = size - dsize - 1;
	i = 0;
	if (dsize < size)
	{
		while (src[i] != '\0' && i < condition)
			dest[dsize++] = src[i++];
		dest[dsize] = '\0';
		return (total_size);
	}
	dest[dsize] = '\0';
	return (ssize + size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len + 1);
	ft_strlcat(new_str, s2, s1_len + s2_len + 1);
	free((char *)s1);
	s1 = NULL;
	free((char *)s2);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_list;
	t_list			*tg_list;
	char			*tmp_str;
	ssize_t			lf_offset;
	ssize_t			null_offset;
	int				result;
	char			*ret_str;

	tg_list = create_or_find_fd_list(&fd_list, fd);
	// tg_listがあった場合もなかった場合も、\nが存在するか検索する
	lf_offset = ft_strchr_index(tg_list->buf, '\n');
	// 改行があった時
	if (lf_offset != -1)
	{
		// 戻り値に返すsubstr: ret_str
		ret_str = ft_substr(tg_list->buf, 0, lf_offset + 1);
		// 保存しておくsubstr: tmp_str
		tmp_str = ft_substr(tg_list->buf, lf_offset + 1, ft_strchr_index(tg_list->buf, '\0'));
		// freeして付け替え
		free(tg_list->buf);
		tg_list->buf = tmp_str;
		return (ret_str);	
	}	
	while (1)
	{
		tmp_str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1UL);
		if (tmp_str == NULL)
			return (NULL);
		result = read(fd, tmp_str, BUFFER_SIZE);
		tmp_str[result] = '\0';
		//もう読みこむファイルが無い時
		if (result <= 0)
		{
			free(tmp_str);
			if (*(tg_list->buf) != '\0')
			{
				ret_str = ft_strdup(tg_list->buf);
				free(tg_list->buf);
				tg_list->buf = NULL;
				free(fd_list);
				fd_list = NULL;
				return (ret_str);
			}
			free(tg_list->buf);
			tg_list->buf = NULL;
			free(fd_list);
			fd_list = NULL;
			return (NULL);
		}
		lf_offset = ft_strchr_index(tmp_str, '\n');
		null_offset = ft_strchr_index(tmp_str, '\0');
		if (lf_offset != -1)
		{
			ret_str = ft_strjoin(tg_list->buf, ft_substr(tmp_str, 0, lf_offset + 1));
			tg_list->buf = ft_substr(tmp_str, lf_offset + 1, null_offset);
			free(tmp_str);
			tmp_str = NULL;
			return (ret_str);
		} else {
			tg_list->buf = ft_strjoin(tg_list->buf, ft_substr(tmp_str, 0, null_offset));
			free(tmp_str);
			tmp_str = NULL;
		}
	}
}
