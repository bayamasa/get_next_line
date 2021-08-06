#include "get_next_line.h"

void	create_fd_list(t_list *list, int fd)
{
	if (!list)
	{
		list = (t_list *)malloc(sizeof(t_list));
		list->fd = fd;
		return ;
	}

	while ()
	{
		/* code */
	}
	
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
	char			*buff;
	char			*line;
	ssize_t			lf;
	//error handling

	//fd_listを確認して値が存在しないことを確認
	create_fd_list(fd_list, fd);

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
