#include "get_next_line.h"

t_list	*create_fd_list(t_list *fd_list, int fd)
{
	if (!fd_list)
	{
		fd_list = (t_list *)malloc(sizeof(t_list));
		fd_list->fd = fd;
		fd_list->buf = "\0";
		return (fd_list);
	}
	fd_list = fd_list->next;
	while (fd_list)
	{
		if (fd_list->fd == fd)
			return (fd_list);
		fd_list = fd_list->next;
	}
	fd_list = (t_list *)malloc(sizeof(t_list));
	fd_list->fd = fd;
	fd_list->buf = "\0";
	return (fd_list);
}

t_list *find_fd_list(t_list *fd_list, int fd)
{
	fd_list
}

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*new_list;

// 	new_list = (t_list *)malloc(sizeof(t_list));
// 	if (new_list == NULL)
// 		return (NULL);
// 	new_list->content = content;
// 	new_list->next = NULL;
// 	return (new_list);
// }

char	*get_next_line(int fd)
{
	static t_list	*fd_list;
	static t_list	*tg_list;

	tg_list = create_fd_list(fd_list, fd);

	// 読み込む文字列用の値をmallocしてあげる必要がある。
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	read(fd, buff, BUFFER_SIZE);
	lf = ft_strchr_index(buff, '\n');
	if (lf != -1)
	{
		fd_list->offset = lf;
		fd_list->fd = fd;
		line = ft_substr(buff, fd_list->offset, lf);
		free(buff);
	}
	return (line);
}
