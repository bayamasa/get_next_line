/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:49:17 by mhirabay          #+#    #+#             */
/*   Updated: 2021/11/28 17:41:23 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *src)
{
	size_t		i;
	size_t		len;
	char		*dest;

	len = 0;
	if (src == NULL)
		return (NULL);
	i = 0;
	while (src[len] != '\0')
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	free(src);
	src = NULL;
	return (dest);
}

char	*read_buffering(char **text, int *status)
{
	ssize_t	index;
	char	*tmp;
	char	*ret;
	ssize_t	text_len;

	ret = NULL;
	text_len = 0;
	if (*text == NULL)
		return (NULL);
	while (*text[text_len] != '\0')
		text_len++;
	index = ft_strchr_index(*text, '\n');
	if (index != -1)
	{
		tmp = ft_substr(*text, index + 1, text_len - (index + 1));
		if (tmp != NULL)
		{
			(*text)[index + 1] = '\0';
			ret = *text;
			*text = tmp;
		}
		else
			*status = -1;
	}
	return (ret);
}

char	*finish(ssize_t read_count, char **text, char *read_res)
{
	ssize_t	index;
	char	*ret;
	size_t	text_len;

	text_len = 0;
	free(read_res);
	ret = NULL;
	if (read_count == 0)
	{
		if (*text == NULL)
			return (NULL);
		while ((*text)[text_len] != '\0')
			text_len++;
		index = ft_strchr_index(*text, '\n');
		if (index == -1)
		{
			if (text_len != 0)
				ret = ft_strdup(*text);
			*text = NULL;
		}
	}
	else
		if (*text != NULL)
			free(*text);
	return (ret);
}

char	*store_buffer_2(char *read_res, char **text, int *status, char *tmp)
{
	char	*ret;
	size_t	tmp_len;

	tmp_len = 0;
	while (tmp[tmp_len] != '\0')
		tmp_len++;
	if (tmp_len == 0)
	{
		free(tmp);
		if (*text != NULL)
		{
			ret = ft_strjoin(*text, read_res);
			free(read_res);
			*text = NULL;
			return (ret);
		}
		return (read_res);
	}
	if (*text == NULL)
		*text = ft_strdup(tmp);
	else
	{
		ret = ft_strjoin(*text, read_res);
		if (ret == NULL)
			*status = -1;
		free(read_res);
		*text = tmp;
		return (ret);
	}
	return (read_res);
}

char	*store_buffer(char *read_res, char **text, int *status)
{
	ssize_t	index;
	char	*tmp;
	size_t	res_len;

	*status = 1;
	res_len = 0;
	index = ft_strchr_index(read_res, '\n');
	if (index == -1)
	{
		if (*text == NULL)
			*text = ft_strdup(read_res);
		else
		{
			*text = ft_strjoin(*text, read_res);
			free(read_res);
		}
		if (*text == NULL)
			*status = -1;
		return (NULL);
	}
	else
	{
		while (read_res[res_len] != '\0')
			res_len++;
		read_res[index + 1] = '\0';
		tmp = ft_substr(read_res, index + 1, res_len - (index + 1));
		if (tmp == NULL)
		{	
			free(read_res);
			*status = -1;
			return (NULL);
		}
		return (store_buffer_2(read_res, text, status, tmp));
	}
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*ret;
	char		*read_res;
	ssize_t		read_count;
	int			status;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	ret = read_buffering(&text, &status);
	if (ret == NULL && status == -1)
		return (NULL);
	if (status == 0 && ret != NULL)
		return (ret);
	while (1)
	{
		read_res = NULL;
		read_res = (char *)malloc(sizeof(char) * (size_t)BUFFER_SIZE + 1);
		read_count = read(fd, read_res, BUFFER_SIZE);
		if (read_count <= 0)
			return (finish(read_count, &text, read_res));
		*(read_res + read_count) = '\0';
		ret = store_buffer(read_res, &text, &status);
		if (status == -1 && ret == NULL)
			return (NULL);
		if (status == 1 && ret != NULL)
			return (ret);
	}
}
