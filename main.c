#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void check_leaks();

int main()
{
	int fd = open("42_with_nl", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));

	// printf("third read %s", get_next_line(fd));
	// printf("third read %s", get_next_line(fd));
	// printf("third read %s", get_next_line(fd));

	// printf("%zu\n", sizeof(t_list));
	// system("leaks a.out");
	// check_leaks();
	return(0);
}
