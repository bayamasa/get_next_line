#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

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


// freeテスト
// ある文字列を作ったときに、その文字列の間にnull文字を置いたときに、
// 最初に作成した文字列はfreeされるのか。
// → される。間にnull文字が置いてあったとしても、最初にmallocで確保した文字列全体がfreeされる。
int	main()
{
	char *a = ft_strdup("hellooooooooooo");
	a[5] = '\0';
	free(a);
	system("leaks a.out");
	return (0);
}
