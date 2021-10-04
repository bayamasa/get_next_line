#include <stdlib.h>
#include <limits.h>
#include <libc.h>

int main()
{
	int i;
	char *a = calloc(SIZE_T_MAX, 1);
	while (i < 50)
	{
		memset(a, 'a', 1000000000);
		i++;
	}
	// a[50000000000] = '\0';
	// printf("%zu", strlen(a));
}
