#include "apue.h"

int g = 6;
int main(void){

    int var;
    pid_t pid;
    
    var = 88;
    printf("before vfork\n");
    
    if ((pid = vfork()) <0 ){
        err_sys("vfork err");
    }else if(pid == 0){
        // 和父进程共享，所以会修改父进程的内存
        g++;
        var++;
        _exit(0);
    }

    printf("pid=%ld,golb=%d,var = %d\n",(long)getpid(), g,var);
    exit(0);
}