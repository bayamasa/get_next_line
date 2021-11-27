#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

// ダブルポインタの間接参照をchar *にしたら値は一致するのかどうかと言う話

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

void copy(char **a)
{
	char *b = ft_strdup("eeeeeeeeee");
	printf("b = %p\n", b);
	printf("b : %s\n", b);
	*a = b;
}

int	main()
{	
	char *a = ft_strdup("helloooo");

	copy(&a);
	printf("a = %p\n", a);
	printf("a : %s\n", a);
	return (0);
}
