#include "get_next_line.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{	
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

t_list	*ft_lstnew(int fd)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (new_list == NULL)
		return (NULL);
	new_list->fd = fd;
	new_list->next = NULL;
	return (new_list);
}

int main()
{
	t_list	*test;
	t_list	*new;

	test = ft_lstnew(5);
	new = ft_lstnew(3);
	printf("before test = %p\n", test);
	ft_lstadd_front(&test, new);
	printf("after new = %p\n", new);
	printf("after test = %p\n", test);
}
