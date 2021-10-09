/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:04:37 by tisoya            #+#    #+#             */
/*   Updated: 2021/09/20 15:04:26 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_gnl_strmove(char *line, size_t len)
{
	size_t	i;

	i = 0;
	while (line[i + len])
	{
		line[i] = line[i + len];
		i++;
	}
	line[i] = '\0';
}

void	ft_gnl_free(char **p1, char **p2)
{
	if (p1)
	{
		free(*p1);
		*p1 = NULL;
	}
	if (p2)
	{
		free(*p2);
		*p2 = NULL;
	}
}

char	*ft_gnl_trim_until_end(char **line, ssize_t rc)
{
	char	*rtn;
	char	*nl_idx;

	rtn = NULL;
	if (rc <= -1)
		ft_gnl_free(&(*line), NULL);
	if ((!line || !*line) && rc <= 0)
		return (NULL);
	nl_idx = ft_strchr(*line, '\n');
	if (nl_idx)
	{
		rtn = ft_substr(*line, 0, nl_idx - *line + 1);
		ft_gnl_strmove(*line, nl_idx - *line + 1);
	}
	else if (*line)
	{
		rtn = ft_strdup(*line);
		ft_gnl_free(&(*line), NULL);
	}
	if (!rtn || !rtn[0])
		ft_gnl_free(&(*line), &rtn);
	return (rtn);
}

char	*get_next_line(int fd)
{
	static char	*line[FD_MAX];
	char		*buf;
	ssize_t		rc;
	char		*nl;

	if (fd < 0 || fd >= FD_MAX || (size_t)BUFFER_SIZE <= 0)
		return (NULL);
	nl = NULL;
	rc = 0;
	buf = (char *)malloc(sizeof(char) * (size_t)BUFFER_SIZE + 1);
	nl = ft_strchr(line[fd], '\n');
	while (!nl && buf)
	{
		rc = read(fd, buf, (size_t)BUFFER_SIZE);
		if (rc <= 0)
			break ;
		buf[rc] = '\0';
		nl = ft_strchr(buf, '\n');
		line[fd] = ft_strjoin_gnl(line[fd], buf);
		if (!line[fd])
			break ;
	}
	free(buf);
	return (ft_gnl_trim_until_end(&line[fd], rc));
}
