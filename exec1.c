#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("In exec 1 \n");
    char *args[] = {"./exec2","exec2"};
    execl(args[0],args[1],NULL);
    return 0;
}