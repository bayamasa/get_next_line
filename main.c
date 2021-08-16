#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void check_leaks();

int main()
{
	// char *a;
	int fd = open("41_no_nl", O_RDONLY);
	// while ((a = get_next_line(fd)) != NULL)
	// {
	// 	while (*a != '\0')
	// 	{
	// 		printf("%d", *a++);
	// 	}
	// }
	printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));


	// system("leaks a.out");
	// check_leaks();
	return(0);
}
