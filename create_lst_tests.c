#include "get_next_line.h"
#include <stdio.h>

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

t_list	*get_list(int fd)
{
	static t_list	*fd_list;
	t_list			*tg_list;

	tg_list = create_or_find_fd_list(&fd_list, fd);
	printf("%d", fd_list->fd);
	return (tg_list);
}

int main()
{
	printf("%d\n", get_list(2)->fd);
	printf("%d\n", get_list(3)->fd);
	printf("%d\n", get_list(4)->fd);
	printf("%d\n", get_list(3)->fd);
}
