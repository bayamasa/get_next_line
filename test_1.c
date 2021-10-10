#include <stdlib.h>
#include <limits.h>
#include <libc.h>
#include "get_next_line.h"
void check_leaks();

int main()
{
	int fd = open("files/no_nl", O_RDONLY);
	char *str1 = get_next_line(fd);	
	printf("str1 : %s\n", str1);
	free(str1);
	close(fd);
	// check_leaks();
	system("leaks a.out");
	return (0);
}

// 9223372036854775807
// 18446744073709551615
