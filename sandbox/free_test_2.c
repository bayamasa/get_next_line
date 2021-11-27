#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>


// 値渡しで渡した関数の中でfreeしたとき、元の確保したポインタはfreeされるのか
// される
char	*ft_strdup(const char *src)
{
	size_t		i;
	size_t		len;
	char		*dest;

	len = 0;
	if (src == NULL)
		return (NULL);
	i = 0;
	while (src[len] != '\0')
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void free_in_func(char *a)
{
	free(a);
}

int	main()
{
	char *a = ft_strdup("helloooooo");
	free_in_func(a);
	// free(a);
	system("leaks a.out");
	return (0);
}
