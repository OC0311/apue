#include "apue.h"
#include <fcntl.h>
#include "./tellwait.c"
#include "./lockreg.c"

static void lockabyte(const char *name,int fd, off_t offset){
    if (write_lock(fd,offset,SEEK_SET,1) < 0){
        err_sys("%s:writew_lock error", name);
    }

    printf("%s:got the lock ,byte %lld\n", name ,(long long )offset);
}


// 在mac 下父子进程都会保存退出，其他的系统不太清楚
int main(void){
    int fd;
    pid_t pid;

    if((fd = creat("./deadlock.pid",FILE_MODE)) < 0){
        err_sys("create error");
    }

    // 写入两个字节
    if(write(fd, "ab", 2) !=2){
        err_sys("write error");
    }

    TELL_WAIT();
    if ((pid = fork()) <0){
        err_sys("fork error");
    }else if(pid == 0){
        lockabyte("child", fd,0);
        TELL_PARENT(getppid());
        WAIT_PARENT();
        lockabyte("child", fd,1);
    }else{
        lockabyte("parent",fd,1);
        TELL_PARENT(pid);
        WAIT_CHILD();
        lockabyte("parent",fd,0);
    }

    exit(0);
}