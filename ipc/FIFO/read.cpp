#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#ifdef __linux__
#include <unistd.h>
#endif

// 不使用cmake编译: g++ read.cpp -g -o ./build/read -D __linux__

int main(int argc, char* argv[])
{

#ifdef __linux__
    if (mkfifo("./build/myfifo", 0666) < 0 && errno != EEXIST)
        perror("create FIFO error.");

    int fd = open("./build/myfifo", O_RDONLY);
    if (fd == -1)
    {
        perror("open error.");
        exit(1);
    }

    char buf[1024] = { 0 };
    // 返回ssize_t,错误返回-1
    while (read(fd, buf, sizeof(buf) - 1) > 0)
    {
        printf("read message: %s", buf);
    }

    close(fd);
#endif
    return 0;
}