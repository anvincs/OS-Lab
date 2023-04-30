#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd;
    char buffer[20] , msg[20]="How are you";
    fd = open("check.txt" , O_RDWR|O_CREAT);
    printf("fd = %d\n",fd);
    if(fd != 1)
    {
        printf("check.txt opened with read write access\n");
        write(fd,msg,sizeof(msg));
        lseek(fd,0,SEEK_SET);
        read(fd,buffer,sizeof(msg));
        printf("%s was written to the file\n",buffer);
        close(fd);
    }
    return 0;
}
