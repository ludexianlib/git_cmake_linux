#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __linux__

void server()
{
    // 创建myfifo权限为0666的命名管道
    if (mkfifo("myfifo", S_FIFO | 0666) == -1)
    {
        perror("mkfifo error.");
        exit(1);
    }

    int fd = open("./myfifo", O_RDWR);
    if (fd == -1)
    {
        perror("open error.");
        exit(2);
    }

    char buf[1024] = { 0 };
    while (true)
    {
        printf("sendto: ");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf) - 1); // 从标准输入获取消息

        if (s > 0)
        {
            if (write(fd, buf, s) == -1)
            {
                perror("write error.");
                exit(3);
            }
        }
    }
    close(fd);
}

#endif

int main(int argc, char* argv[])
{

#ifdef __linux__
    server();
#endif
    return 0;
}