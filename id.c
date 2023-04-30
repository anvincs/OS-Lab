#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    int ret = fork();
    if(ret == 0)
    {
        printf("Child process\n");
        printf("Child id : %d\n",getpid());
        printf("Parent id : %d\n",getppid());
    }
    else
    {
        printf("Parent process\n");
        printf("Process id : %d\n",getpid());
        printf("Parent id : %d\n",getppid());
    }

    return 0;
}