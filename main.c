#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void check_leaks();

int main()
{
	char *a;
	char *b;
	char *c;
	char *d;
	char *e;
	char *f;
	// char *g;
	// char *h;
	// char *j;
	// char *k;

	int fd = open("multiple_nlx5", O_RDONLY);
	// while ((a = get_next_line(fd)) != NULL)
	// {
	// 	printf("%s", a);
	// 	free(a);
	// }
	a = get_next_line(fd);
	b = get_next_line(fd);
	c = get_next_line(fd);
	d = get_next_line(fd);
	e = get_next_line(fd);
	f = get_next_line(fd);
	// g = get_next_line(fd);
	// h = get_next_line(fd);
	// j = get_next_line(fd);
	// k = get_next_line(fd);
	// close(fd);
	printf("%s", a);
	printf("%s", b);
	printf("%s", c);
	printf("%s", d);
	printf("%s", e);
	printf("%s", f);
	// printf("%s", g);
	// printf("%s", h);
	// printf("%s", j);
	// printf("%s", k);
	free(a);
	free(b);
	free(c);
	free(d);
	free(e);
	free(f);
	// free(g);
	// free(h);
	// free(j);
	// free(k);
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// system("leaks a.out");
	check_leaks();
	return(0);
}
