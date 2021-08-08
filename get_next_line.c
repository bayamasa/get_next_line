#include "get_next_line.h"

t_list	*create_or_find_fd_list(t_list **fd_list, int fd)
{
	if (!*fd_list)
	{
		*fd_list = (t_list *)malloc(sizeof(t_list));
		(*fd_list)->fd = fd;
		(*fd_list)->buf = "\0";
		return (*fd_list);
	}
	while ((*fd_list)->next)
	{
		if ((*fd_list)->fd == fd)
			return (*fd_list);
		(*fd_list) = (*fd_list)->next;
	}
	(*fd_list) = (t_list *)malloc(sizeof(t_list));
	(*fd_list)->fd = fd;
	(*fd_list)->buf = "\0";
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

	tg_list = create_or_find_fd_list(fd_list, fd);
	while (1)
	{
		tmp_str = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		result = read(fd, tmp_str, BUFFER_SIZE);
		if (result <= 0)
		{
			//今まで当てたt_list側もfreeしないといけない。
			free(tmp_str);
			return (NULL);
		}
		lf_offset = ft_strchr_index(tmp_str, '\n');
		if (lf_offset != -1)
		{
			null_offset = ft_strchr_index(tmp_str, '\0');
			tg_list->buf = ft_strjoin(tg_list->buf, \
				ft_substr(tmp_str, lf_offset, null_offset));
			free(tmp_str);
			return (ft_substr(tmp_str, 0, lf_offset));
		}else {
			tg_list->buf = ft_strjoin(tg_list->buf, \
				ft_substr(tmp_str, 0, BUFFER_SIZE));
		}
		free(tmp_str);
	}
}
