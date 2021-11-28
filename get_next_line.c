/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:49:17 by mhirabay          #+#    #+#             */
/*   Updated: 2021/11/28 14:24:59 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *src)
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
	return (dest);
}

char	*read_buffering(char **text, int *status)
{
	ssize_t	index;
	char	*tmp;
	char	*ret;

	*status = 1;
	if (*text == NULL)
		return (NULL);
	index = ft_strchr_index(*text, '\n');
	if (index == -1)
		return (NULL);
	else
	{
		tmp = ft_substr(*text, index + 1, ft_strlen(*text) - (index + 1));
		if (tmp == NULL)
		{
			*status = -1;
			return (NULL);
		}			
		(*text)[index + 1] = '\0';
		ret = *text;
		*text = tmp;
		return (ret);
	}
}

char	*finish(ssize_t read_count, char **text, char *read_res)
{
	ssize_t	index;
	char	*tmp;
	char	*ret;
	size_t	text_len;

	free(read_res);
	if (read_count == 0)
	{
		if (*text == NULL)
			return (NULL);
		index = ft_strchr_index(*text, '\n');
		if (index == -1)
		{	
			if (ft_strlen(*text) == 0)
			{
				free(*text);
				*text = NULL;
				return (NULL);
			}
			ret = ft_strdup(*text);
			free(*text);
			*text = NULL;
			return (ret);
		}
		else
		{
			tmp = ft_substr(*text, index, ft_strlen(*text) - index);
			if (tmp == NULL)
				return (NULL);
			*text[index] = '\0';
			ret = *text;
			*text = tmp;
			return (ret);
		}
	}
	if (read_count == -1)
	{
		if (*text != NULL)
			free(*text);
		return (NULL);
	}
	return (NULL);
}

char	*store_buffer(char *read_res, char **text, int *status)
{
	ssize_t	index;
	char	*tmp;
	char	*ret;

	*status = 1;
	index = ft_strchr_index(read_res, '\n');
	if (index == -1)
	{
		if (*text == NULL)
		{
			*text = ft_strdup(read_res);
			free(read_res);
			*status = 1;
			return (NULL);
		}
		*text = ft_strjoin(*text, read_res);
		if (*text == NULL)
		{
			*status = -1;
			return (NULL);
		}
		free(read_res);
		return (NULL);
	}
	else
	{
		tmp = ft_substr(read_res, index + 1, ft_strlen(read_res) - (index + 1));
		if (tmp == NULL)
		{	
			free(read_res);
			*status = -1;
			return (NULL);
		}
		read_res[index + 1] = '\0';
		if (ft_strlen(tmp) == 0)
		{
			if (*text != NULL)
			{
				ret = ft_strjoin(*text, read_res);
				free(read_res);
				free(tmp);
				*text = NULL;
				return (ret);
			}
			free(tmp);
			return (read_res);
		}
		if (*text == NULL)
		{
			*text = ft_strdup(tmp);
			free(tmp);
			return (read_res);
		}
		else
		{
			ret = ft_strjoin(*text, read_res);
			if (ret == NULL)
			{
				free(read_res);
				*status = -1;
				return (NULL);
			}
			free(read_res);
			*text = tmp;
			return (ret);
		}
		*status = 1;
		return (read_res);
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
	if (status == 1 && ret != NULL)
		return (ret);
	while (1)
	{
		read_res = (char *)malloc(sizeof(char) * (size_t)BUFFER_SIZE + 1);
		read_count = read(fd, read_res, BUFFER_SIZE);
		*(read_res + read_count) = '\0';
		if (read_count <= 0)
			return (finish(read_count, &text, read_res));
		ret = store_buffer(read_res, &text, &status);
		if (status == -1 && ret == NULL)
			return (NULL);
		if (status == 1 && ret != NULL)
			return (ret);
	}
}
