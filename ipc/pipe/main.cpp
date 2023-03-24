#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__

#include <sys/wait.h>
#include <unistd.h>

#endif

int main(int argc, char* argv[])
{

#ifdef __linux__

    // create_pipe[0]: read, create_pipe[1]: write
    int create_pipe[2] = {0, 0};
    if (pipe(create_pipe) == -1)
    {
        perror("create pipe error.");
        return 1;
    }
    printf("create_pipe[0] is %d, create_pipe[1] is %d\n", create_pipe[0], create_pipe[1]);
    
    pid_t id = fork(); // 父进程fork子进程
    if (id < 0)
    {
        perror("fork error.");
        return 2;
    }
    else if (id == 0) // 子进程写
    {
        printf("child process write.\n");
        // 如果子进程写则关闭读端
        close(create_pipe[0]);

        int count = 5;
        const char* msg = "this is from child process.";
        while(count--)
        {
            write(create_pipe[1], msg, strlen(msg));
            sleep(1);
        }

        close(create_pipe[1]);
        exit(1);
    }
    else // 父进程读
    {
        printf("father process reading.\n");
        // 如果父进程读则关闭写端
        close(create_pipe[1]);

        char msg[1024] = { 0 };
        int count = 5;
        while (count--)
        {
            ssize_t s = read(create_pipe[0], msg, sizeof(msg) - 1);
            if (s > 0)
            {
                printf("client: %s\n", msg);
            }
            else
            {
                perror("read error.");
                exit(1);
            }
        }

        if (waitpid(id, nullptr, 0) != -1)
        {
            printf("wait success.\n");
        }
    }

#endif

    return 0;
}