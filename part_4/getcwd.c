#include "apue.h"

char* path_allocv2(int* size)
{
    char *p = NULL;
    if(!size) return NULL;
        p = malloc(256);
    if(p)
        *size = 256;
    else
        *size = 0;  
    return p;
}

int main(void){

    char *ptr;
    int size;

    // 改变当前目录
    if (chdir("/Users/rjj/learn/apue/part_3") <0 ){
        err_sys("chdir failed!");
    }
    ptr = path_allocv2(&size);
    if (getcwd(ptr,size) == NULL){
        err_sys("getcwd failed");

    }

    printf("cwd = %s\n",ptr);
    exit(0);
}