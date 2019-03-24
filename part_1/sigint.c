#include "apue.h"
#include<sys/wait.h>

static void sig_int(int);

static void sig_int(int sig){
    printf("出错啦  好运来！");
}

int main(){
    char buf[MAXLINE];
    pid_t pid;
    int status;

    // 捕获信号
    if (signal(SIGINT, sig_int) ==SIG_ERR){
        err_sys("signal error");
    }

    // 可以支持传入参数
    printf("%% " );
    while(fgets(buf,MAXLINE,stdin) != NULL){
    
        if (buf[strlen(buf)-1] == '\n'){
            buf[strlen(buf)-1] = 0;
        }

        if ((pid = fork()) < 0){
            printf("dfadf");
            err_sys("fork error");
            // 子进程的pid 为0 fork 会返回两次，一次在父进程中，一次在子进程中
        }else if(pid == 0){
            execlp(buf, buf, (char *)0);
            err_ret("not exec!");
            exit(127);
        }
    
        if ((pid=waitpid(pid, &status,0)) < 0){
            err_sys("wait pid");
        }
        printf("%% ");
    }

    exit(0);
}