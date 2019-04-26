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

    ptr = path_allocv2(&size);

    
    int pid;

    if ((pid = fork()) < 0){
        err_sys("fork err");
    }else if(pid == 0){
        // 子进程修改当前目录后  父进程的当前目录不会改变
        int i;
        if ((i = chdir("/tmp"))<  0){
            err_sys("chdir err");
        }
        if (getcwd(ptr, size) == NULL){
            err_sys("get cwd err");
        }
        printf("chaild cwd = %s \n",ptr);
    }else{
         if (getcwd(ptr, size) == NULL){
            err_sys("get cwd err");
        }
        printf("parenrt cwd = %s \n",ptr);
    }


    
}
