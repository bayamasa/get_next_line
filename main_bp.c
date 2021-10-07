#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void check_leaks();

int main()
{
	int fd = open("gnl_tester/files/no_nl", O_RDONLY);
	printf("%s", get_next_line(fd));
	return(0);
}
