/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:01:44 by mhirabay          #+#    #+#             */
/*   Updated: 2021/11/29 07:59:00 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

# define TEST_NO_NL "TEST_NO_NL"
# define TEST_NL "TEST_NL"
# define TEST_EMPTY "TEST_EMPTY"
# define TEST_WITH_NL "TEST_WITH_NL"
# define TEST_MULTIPLE_LINE_NO_NL "TEST_MULTIPLE_LINE_NO_NL"
# define TEST_MULTIPLE_LINE_WITH_NL "TEST_MULTIPLE_LINE_WITH_NL"
# define TEST_MUTIPLE_LINE_AND_NL_EOF_NL "TEST_MUTIPLE_LINE_AND_NL_EOF_NL"
# define TEST_BIG_LINE_WITH_NL "TEST_BIG_LINE_WITH_NL"
# define BONUS_MULTIPLE_OPEN "BONUS_MULTIPLE_OPEN"

void	expect_str(char *str1, char *str2, char *test_target)
{
	if (str1 == NULL && (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX))
	{
		printf("OK : BUFFER_SIZE IS NULL\n");
		return ;
	}
	if (str1 == NULL)
	{
		printf("ERR : RES IS NULL\n");
		return ;
	}
	if (strcmp(str1, str2) == 0)
	{
		printf("OK : %s \n", test_target);
	}
	else
	{
		printf("KO : %s \n", test_target);
		printf("actual : %s\n", str1);
		printf("expect : %s\n", str2);
	}
}

void	expect_null(char *str, char *test_target)
{
	if (str == NULL)
	{
		printf("OK : NULL CHECK %s\n", test_target);
	}
	else
	{
		printf("KO : %s \n", test_target);
	}
}

void test_no_nl()
{
	int fd = open("files/no_nl", O_RDONLY);
	char *str1 = get_next_line(fd);
	char *str2 = get_next_line(fd);	
	expect_str(str1, "01234567890123456789012345678901234567890", TEST_NO_NL);
	expect_null(str2, TEST_NO_NL);
	free(str1);
	free(str2);
	close(fd);
}

void test_nl()
{
	int fd = open("files/nl", O_RDONLY);
	char *str1 = get_next_line(fd);
	char *str2 = get_next_line(fd);
	expect_str(str1, "\n", TEST_NL);
	expect_null(str2, TEST_NL);
	free(str1);
	free(str2);
	close(fd);
}

void test_empty()
{
	int fd = open("files/empty", O_RDONLY);
	char *str1 = get_next_line(fd);	
	expect_null(str1, TEST_EMPTY);
	close(fd);
}

void test_with_nl()
{
	int fd = open("files/with_nl", O_RDONLY);
	char *str1 = get_next_line(fd);
	char *str2 = get_next_line(fd);
	char *str3 = get_next_line(fd);
	expect_str(str1, "0123456789012345678901234567890123456789\n", TEST_WITH_NL);
	expect_str(str2, "0", TEST_WITH_NL);
	expect_null(str3, TEST_WITH_NL);
	free(str1);
	free(str2);
	close(fd);
}
void test_multiple_line_no_nl()
{
	int fd = open("files/multiple_line_no_nl", O_RDONLY);
	char *str1 = get_next_line(fd);
	char *str2 = get_next_line(fd);
	char *str3 = get_next_line(fd);
	char *str4 = get_next_line(fd);
	char *str5 = get_next_line(fd);
	char *str6 = get_next_line(fd);

	expect_str(str1, "01234567890123456789012345678901234567890\n", TEST_MULTIPLE_LINE_NO_NL);
	expect_str(str2, "987654321098765432109876543210987654321098\n", TEST_MULTIPLE_LINE_NO_NL);
	expect_str(str3, "0123456789012345678901234567890123456789012\n", TEST_MULTIPLE_LINE_NO_NL);
	expect_str(str4, "987654321098765432109876543210987654321098\n", TEST_MULTIPLE_LINE_NO_NL);
	expect_str(str5, "01234567890123456789012345678901234567890", TEST_MULTIPLE_LINE_NO_NL);
	expect_null(str6, TEST_MULTIPLE_LINE_NO_NL);
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	close(fd);
}

void test_multiple_line_with_nl()
{
	int fd = open("files/multiple_line_with_nl", O_RDONLY);
	char *str1 = get_next_line(fd);
	char *str2 = get_next_line(fd);
	char *str3 = get_next_line(fd);
	char *str4 = get_next_line(fd);
	char *str5 = get_next_line(fd);
	char *str6 = get_next_line(fd);

	expect_str(str1, "9876543210987654321098765432109876543210\n", TEST_MULTIPLE_LINE_WITH_NL);
	expect_str(str2, "01234567890123456789012345678901234567890\n", TEST_MULTIPLE_LINE_WITH_NL);
	expect_str(str3, "987654321098765432109876543210987654321098\n", TEST_MULTIPLE_LINE_WITH_NL);
	expect_str(str4, "01234567890123456789012345678901234567890\n", TEST_MULTIPLE_LINE_WITH_NL);
	expect_str(str5, "9876543210987654321098765432109876543210\n", TEST_MULTIPLE_LINE_WITH_NL);
	expect_null(str6, TEST_MULTIPLE_LINE_WITH_NL);
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	close(fd);
}

void test_mutiple_line_and_nl_eof_nl()
{
	int fd = open("files/mutiple_line_and_nl_eof_nl", O_RDONLY);
	char *str1 = get_next_line(fd);
	char *str2 = get_next_line(fd);
	char *str3 = get_next_line(fd);
	char *str4 = get_next_line(fd);
	char *str5 = get_next_line(fd);
	char *str6 = get_next_line(fd);
	char *str7 = get_next_line(fd);
	char *str8 = get_next_line(fd);
	char *str9 = get_next_line(fd);
	char *str10 = get_next_line(fd);

	expect_str(str1, "01234567890123456789012345678901234567890\n", TEST_MUTIPLE_LINE_AND_NL_EOF_NL);
	expect_str(str2, "\n", TEST_MUTIPLE_LINE_AND_NL_EOF_NL);
	expect_str(str3, "987654321098765432109876543210987654321090\n", TEST_MUTIPLE_LINE_AND_NL_EOF_NL);
	expect_str(str4, "\n", TEST_MUTIPLE_LINE_AND_NL_EOF_NL);
	expect_str(str5, "0123456789012345678901234567890123456789012\n", TEST_MUTIPLE_LINE_AND_NL_EOF_NL);
	expect_str(str6, "\n", TEST_MUTIPLE_LINE_AND_NL_EOF_NL);
	expect_str(str7, "987654321098765432109876543210987654321090\n", TEST_MUTIPLE_LINE_AND_NL_EOF_NL);
	expect_str(str8, "\n", TEST_MUTIPLE_LINE_AND_NL_EOF_NL);
	expect_str(str9, "01234567890123456789012345678901234567890\n", TEST_MUTIPLE_LINE_AND_NL_EOF_NL);
	expect_null(str10, TEST_MUTIPLE_LINE_AND_NL_EOF_NL);
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	free(str6);
	free(str7);
	free(str8);
	free(str9);
	close(fd);
}

void test_big_line_with_nl()
{
	int fd = open("files/big_line_with_nl", O_RDONLY);
	char *str1 = get_next_line(fd);
	char *str2 = get_next_line(fd);
	expect_str(str1, "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678\n", TEST_BIG_LINE_WITH_NL);
	expect_null(str2, TEST_BIG_LINE_WITH_NL);
	free(str1);
	close(fd);
}

void bonus_multiple_open()
{
	int fd1 = open("files/no_nl", O_RDONLY);
	int fd2 = open("files/with_nl", O_RDONLY);
	int fd3 = open("files/multiple_line_with_nl", O_RDONLY);
	char *str1 = get_next_line(fd1);
	printf("1\n");
	char *str2 = get_next_line(fd2);
	printf("2\n");
	char *str3 = get_next_line(fd3);
	printf("3\n");	
	char *str4 = get_next_line(fd1);
	printf("4\n");
	char *str5 = get_next_line(fd2);
	printf("5\n");
	char *str6 = get_next_line(fd3);
	char *str7 = get_next_line(fd2);
	char *str8 = get_next_line(fd3);
	char *str9 = get_next_line(fd3);
	char *str10 = get_next_line(fd3);
	char *str11 = get_next_line(fd3);

	expect_str(str1, "01234567890123456789012345678901234567890", BONUS_MULTIPLE_OPEN);
	expect_str(str2, "0123456789012345678901234567890123456789\n", BONUS_MULTIPLE_OPEN);
	expect_str(str3, "9876543210987654321098765432109876543210\n", BONUS_MULTIPLE_OPEN);
	expect_null(str4, BONUS_MULTIPLE_OPEN);
	expect_str(str5, "0", BONUS_MULTIPLE_OPEN);
	expect_str(str6, "01234567890123456789012345678901234567890\n", BONUS_MULTIPLE_OPEN);
	expect_null(str7, BONUS_MULTIPLE_OPEN);
	expect_str(str8, "987654321098765432109876543210987654321098\n", BONUS_MULTIPLE_OPEN);
	expect_str(str9, "01234567890123456789012345678901234567890\n", BONUS_MULTIPLE_OPEN);
	expect_str(str10, "9876543210987654321098765432109876543210\n", BONUS_MULTIPLE_OPEN);
	expect_null(str11, BONUS_MULTIPLE_OPEN);
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	free(str6);
	free(str7);
	free(str8);
	free(str9);
	free(str10);
	free(str11);
}

void test_invalid_fd()
{
	int fd = open("files/no_nl", O_RDONLY);
	close(fd);
	printf("fd = %d\n", fd);
	char *a = get_next_line(fd);
	char *b = get_next_line(fd);
	char *c = get_next_line(10000);
	// char *d = get_next_line(-1);
	free(a);
	free(b);
	free(c);
}

// int main()
// {
// 	printf("--------------------------------\n");
// 	test_no_nl();
// 	test_nl();
// 	test_empty();
// 	test_with_nl();
// 	test_multiple_line_no_nl();
// 	test_multiple_line_with_nl();
// 	test_mutiple_line_and_nl_eof_nl();

// 	test_big_line_with_nl();
// 	get_next_line(50);
// 	test_invalid_fd();
// 	printf("--------------------------------\n");
// 	system("leaks a.out");
// 	return (0);
// }

// #include "leaks_checker.c"

int main()
{
	int fd = open("files/multiple_nlx5", O_RDONLY);
	char *str1 = get_next_line(fd);
	printf("str1 : %s\n", str1);
	free(str1);
	char *str2 = get_next_line(fd);
	printf("str2 : %s\n", str2);
	free(str2);
	char *str3 = get_next_line(fd);
	printf("str3 : %s\n", str3);
	free(str3);

	char *str4 = get_next_line(fd);
	printf("str4 : %s\n", str4);
	free(str4);

	char *str5 = get_next_line(fd);
	printf("str5 : %s\n", str5);
	free(str5);
	
	char *str6 = get_next_line(fd);
	printf("str6 : %s\n", str6);
	free(str6);
	char *str7 = get_next_line(fd);
	printf("str7 : %s\n", str7);
	free(str7);
	// char *str8 = get_next_line(fd);
	// printf("str8 : %s\n", str8);
	// free(str8);
	// char *str9 = get_next_line(fd);
	// printf("str9 : %s\n", str9);
	// free(str9);
	// char *str10 = get_next_line(fd);
	// printf("str10 : %s\n", str10);
	// free(str10);

	
	// char *str6 = get_next_line(fd);

	// printf("str1 : %s\n", str1);
	// printf("str2 : %s\n", str2);
	// printf("str3 : %s\n", str3);
	// printf("str4 : %s\n", str4);
	// printf("str5 : %s\n", str5);
	// printf("str6 : %s\n", str6);



	// printf("%s",str6);
	// free(str6);

	close(fd);
	// check_leaks();
	system("leaks a.out");

}
// 読み込んだ後にもう一回freeしたらどうなるか確認するテストを追加
