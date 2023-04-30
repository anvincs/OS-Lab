#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>

int main()
{
    struct dirent *de;
    DIR *dir = opendir(".");
    if(dir == NULL)
    {
        printf("Opening failed\n");
        exit(0);
    }
    while((de = readdir(dir)) != NULL)
    {
        printf("%s\n",de->d_name);
    }
    closedir(dir);
    return 0;
}