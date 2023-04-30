#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    fork();
    printf("Using fork() system call to create a process\n");
    return 0;
}
