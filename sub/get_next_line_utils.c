/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:05:04 by tisoya            #+#    #+#             */
/*   Updated: 2021/09/20 01:38:57 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	u_c;

	if (!s)
		return (NULL);
	str = (unsigned char *)s;
	u_c = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == u_c)
			break ;
		i++;
	}
	if (str[i] == u_c)
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	size_t			i;
	size_t			len;
	unsigned char	*dup;
	unsigned char	*p;

	len = ft_strlen(src);
	p = (unsigned char *)src;
	dup = (unsigned char *)malloc(sizeof(unsigned char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (p[i])
	{
		dup[i] = p[i];
		i++;
	}
	dup[i] = '\0';
	return ((char *)dup);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	unsigned char	*join;
	size_t			i;
	size_t			j;

	j = 0;
	i = 0;
	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2)
		return (NULL);
	join = (unsigned char *)malloc(sizeof(unsigned char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i])
		join[j++] = (unsigned char)s1[i++];
	i = 0;
	while (s2[i])
		join[j++] = (unsigned char)s2[i++];
	join[j] = '\0';
	free(s1);
	return ((char *)join);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	str_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		return (ft_strdup(""));
	str_len = s_len - (size_t)start;
	if (str_len > len)
		str_len = len;
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)(s + start), str_len + 1);
	return (str);
}
