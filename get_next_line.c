/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:49:17 by mhirabay          #+#    #+#             */
/*   Updated: 2021/11/27 16:54:32 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define MYDEBUG() 

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
	// free((void *)src);
	return (dest);
}

char	*read_buffering(char **text, int *status)
{
	ssize_t	index;
	char *tmp;
	char *ret;

	if (*text == NULL)
	{
		// text = ft_strdup("");
		*status = 1;
		return (NULL);
	}
	// 
	index = ft_strchr_index(*text, '\n');
	// indexに改行が存在しない場合、処理を修了する。
	if (index == -1)
	{
		*status = 1;
		
		return (NULL);
	}
	else
	{
		//tmpには何かが入ってる
		// 2文字何かしらが入っている
		
		tmp = ft_substr(*text, index + 1, ft_strlen(*text) - (index + 1));
		if (tmp == NULL)
		{
			// なんかしらのleak対策が必要かも
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
	ssize_t index;
	char *tmp;
	char *ret;

	// 
	// readが正常に完了したとき
	free(read_res);
	if (read_count == 0)
	{
		if (*text == NULL)
		{
			return (NULL);
		}
		index = ft_strchr_index(*text, '\n');
		// 改行が存在しない
		if (index == -1)
		{	
			// 
			ret = ft_strdup(*text);
			free(*text);
			*text = NULL;
			return (ret);
		}
		// 改行が存在する
		else
		{
			tmp = ft_substr(*text, index, ft_strlen(*text) - index);
			if (tmp == NULL)
			{
				// なんかしらのleak対策が必要かも
				return (NULL);
			}
			*text[index] = '\0';
			ret = *text;
			*text = tmp;
			return (ret);
		}
	}
	// readが異常終了したとき
	if (read_count != -1)
	{
		free(*text);
		free(read_res);
		return (NULL);
	}
	return (NULL);
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
		// free((char *)s1);
		// free((char *)s2);
		return (NULL);
	}
	ft_strlcpy(new_str, s1, s1_len + 1);
	ft_strlcpy(new_str + s1_len, s2, s1_len + s2_len + 1);
	// free((char *)s1);
	s1 = NULL;
	// free((char *)s2);
	return (new_str);
}

ssize_t	ft_strlen(const char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

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
	// str = NULL; 
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

char	*store_buffer(char *read_res, char **text, int *status)
{
	// strlcpyじゃ追加の文字列を追加する時の動的メモリを確保していないのでsegvになる可能性がある。
	ssize_t	index;
	char 	*tmp;

	// 
	index = ft_strchr_index(read_res, '\n');
	// read_resで改行がない場合
	if (index == -1)
	{
		//strjoinに渡した変数はかえって来れなくする
		//
		if (*text == NULL)
		{
			// ここでread_resで付け替えたからfreeに注意
			// *text = read_res;
			*text = ft_strdup(read_res);
			free(read_res);
			// read_res = NULL;
			*status = 1;
			return (NULL);
		}
		*text = ft_strjoin(*text, read_res);
		if(*text == NULL)
		{
			*status = -1;
			return (NULL);
		}
		return (*text);
	}
	else
	{
		
		// read_resで改行がある場合
		// 後半部分を抜き出す
		// 改行文字も含めるのでindex + 1
		tmp = ft_substr(read_res, index + 1, ft_strlen(read_res) - (index + 1));
		// tmpがない場合、tmpは""を返すがgnlはnullを返さないといけない
		// 改行の後に何も存在しない場合は正常系となるので、正常系に置いてもtmpがnullになるケースは存在する
		
		if (tmp == NULL)
		{	
			
			free(read_res);
			*status = -1;
			return (NULL);
		}
		// 文字列の途中でヌル文字を入れたときに、freeしたらleakする？
		// → leakしない。
		// read_resの改行をnull文字にして、gnlの戻り値に設定する。
		read_res[index + 1] = '\0';
		// 
		if (ft_strlen(tmp) == 0)
		{
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
			*text = ft_strjoin(*text, tmp);
			if (*text == NULL)
			{
				free(read_res);
				*status = -1;
				return (NULL);
			}
		}
		*status = 1;
		// 改行の入っている文字列を返す
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

	// readしたやつを読み取る
	// 
	ret = read_buffering(&text, &status);
	if (ret == NULL && status == -1)
		return (NULL);
	if (ret != NULL && status == 1)
		return (ret);
	while (1)
	{
		read_res = (char *)malloc(sizeof(char) * (size_t)BUFFER_SIZE + 1);
		read_count = read(fd, read_res, BUFFER_SIZE);
		*(read_res + read_count) = '\0';
		if (read_count <= 0)
			return (finish(read_count, &text, read_res));
		ret = store_buffer(read_res, &text, &status);
		// free(read_res);
		if (status == -1 && ret == NULL)
			return (NULL);
		if (status == 1 && ret != NULL)
		{
			
			return (ret);
		}
			
	}
}
