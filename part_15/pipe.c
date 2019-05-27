#include "apue.h"

int main(void){
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    if (pipe(fd) < 0){
        err_sys("pipe error");
    }

    if ((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid > 0){
        // 关闭读取的？？？
        // 因为子进程会复制文件描述符
        // 每个文件描述符都会有两个连接
        // 所以父进程先关闭fd[0]
        // 子进程需要关闭fd[1]
        close(fd[0]);
        write(fd[1],"hello world\n",12);
    }else{
    
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO,line, n);
    }

    exit(0);
}