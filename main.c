#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
        int     fd;
        char    buff[100+1];
        int     rc;

        fd = open("test.txt", O_RDONLY);
        if (fd == -1)
        {
                printf("ファイルオープンエラー\n");
			return(0);
        }
        rc = read(fd, buff, 5);
        if (rc == -1)
        {
                printf("ファイル読み込みエラー\n");
        }
        else
        {
                // buff[rc] = '\0';
                printf("read:%d - %s\n", rc, buff);
        }
        close(fd);
		return(0);
}
