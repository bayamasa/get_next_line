/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:38:08 by mhirabay          #+#    #+#             */
/*   Updated: 2021/11/28 15:33:33 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			size;

	size = 0;
	if (s == NULL)
		return (NULL);
	while (s[size] != '\0')
		size++;
	if (size < start)
	{
		return (ft_strdup(""));
	}
	if (size < len)
		len = size;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = 0;
	s2_len = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[s1_len] != '\0')
		s1_len++;
	while (s2[s2_len] != '\0')
		s2_len++;
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (new_str == NULL)
	{
		free((char *)s1);
		return (NULL);
	}
	ft_strlcpy(new_str, s1, s1_len + 1);
	ft_strlcpy(new_str + s1_len, s2, s1_len + s2_len + 1);
	free((char *)s1);
	s1 = NULL;
	return (new_str);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i] != '\0')
		i++;
	if (size == 0)
		return (i);
	while (*src && (size - 1))
	{
		*dest++ = *src++;
		size--;
	}
	*dest = '\0';
	return (i);
}

ssize_t	ft_strchr_index(const char *s, int c)
{
	ssize_t		i;
	char		chr;

	i = 0;
	chr = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == chr)
		{
			return (i);
		}
		i++;
	}
	if (chr == '\0')
		return (i);
	return (-1);
}
