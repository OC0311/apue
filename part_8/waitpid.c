#include "apue.h"
#include <sys/wait.h>

int main(void){
    pid_t pid;
    if ((pid = fork()) < 0){
        err_sys("fork error1");
    }else if(pid == 0){
        if ((pid = fork()) <0 ){
            err_sys("fork error2");
        }else if(pid > 0){
            // 让父进程挂了
            exit(0);
        }
        // 子进程等待两秒
        sleep(10);
        printf("second child parent pid = %ld\n",(long)getppid);
        exit(0);
    }
    if (waitpid(pid, NULL,0) != pid){
        err_sys("wait pid err");
    }

    exit(0);
}