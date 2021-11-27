#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int main()
{
	int fd = open("files/with_nl", O_RDONLY);
	char *str1 = get_next_line(fd);
	char *str2 = get_next_line(fd);
	char *str3 = get_next_line(fd);

	
	printf("str1 : %s\n", str1);
	printf("str2 : %s\n", str2);
	printf("str3 : %s\n", str3);
	
	free(str1);
	free(str2);
	free(str3);
	close(fd);
	// check_leaks();
	// system("leaks a.out");

}
