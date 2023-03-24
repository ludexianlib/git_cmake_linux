#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef __linux__
void client()
{
    int fd = open("./myfifo", O_RDWR);
    if (fd == -1)
    {
        perror("open error.");
        exit(1);
    }

    char buf[1024] = { 0 };
    while (true)
    {
        ssize_t s = read(fd, buf, sizeof(buf) - 1);
        if (s > 0)
        {
            printf("client: %s\n", buf);
        }
        else
        {
            perror("open error.");
            exit(2);
        }
    }
    close(fd);
}
#endif

int main(int argc, char* argv[])
{

#ifdef __linux__
    client();
#endif
    return 0;
}