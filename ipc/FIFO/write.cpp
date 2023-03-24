#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#ifdef __linux__
#include <unistd.h>
#endif

// 不使用cmake编译: g++ read.cpp -g -o ./build/read -D __linux__

int main(int argc, char* argv[])
{

#ifdef __linux__
    printf("process id: %d.\n", getpid());
    // 创建myfifo命名管道
    int fd = open("./build/myfifo", O_WRONLY);
    if (fd == -1)
    {
        perror("open error.");
        exit(1);
    }
    
    time_t tp;
    int n;
    char buf[1024] = { 0 };
    for (int i = 0; i < 10; i++)
    {
        time(&tp);
        // 写入buf，返回长度
        n = sprintf(buf, "process %d's time is %s", getpid(), ctime(&tp));
        printf("send message: %s", buf);
        if (write(fd, buf, n + 1) < 0)
        {
            perror("write FIFO error.");
            close(fd);
            exit(1);
        }
        sleep(1);
    }

    close(fd);
#endif
    return 0;
}