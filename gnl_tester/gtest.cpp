#include <gtest/gtest.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

extern "C"
{
	#include "../get_next_line.h"
}

/* *******
 * printf
 *********/


TEST(get_next_line, no_specifier1)
{
	int fd = open("files/no_nl", O_RDONLY);
	// int number = errno;
	// printf("fd = %d\n", fd);
	// printf("strerr = %s", strerror(number));
	// char *tmp_str = (char *)malloc(sizeof(char) * 100);
	// int result = read(fd, tmp_str, 10);
	// tmp_str[11] = '\0';
	char *str = get_next_line(fd);
	// printf("get_next_line = %s\n", tmp_str);
	EXPECT_STREQ(str, "01234567890123456789012345678901234567890");
	// EXPECT_EQ(res1, res2);
}
