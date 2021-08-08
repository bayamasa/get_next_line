#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void my_read(int fd)
{
	void *buf;
	int result;
	buf = malloc(1);
	result = read(fd, buf, 12);
	printf("buf = %s\n", (char *)buf);	
	printf("result = %d\n", result);

}

int main()
{
	int fd;
	fd = open("test", O_RDONLY);
	my_read(fd);
	my_read(fd);
}
