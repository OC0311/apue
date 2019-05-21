#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./tellwait.c"
#include "./lockreg.c"

int main(int argc, char *argv[]){
    int fd;
    pid_t pid;
    char buf[5];
    struct stat statbuf;
    int val;

    if (argc != 2){
        fprintf(stderr, "usage:%s file name\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,FILE_MODE)) <0 ){
        err_sys("open error");
    }

    if (write(fd,"abcdef",6) != 6){
        err_sys("write error");
    }

    if(fstat(fd,&statbuf) <0){
        err_sys("fstat error");
    }

    if(fchmod(fd,(statbuf.st_mode & ~S_IXGRP) | S_ISGID) <0){
        err_sys("fchmod error");
    }

    TELL_WAIT();

    if((pid = fork()) <0){
        err_sys("open error");
    }else if(pid >0){
        if (write_lock(fd,0,SEEK_SET,0) <0){
            err_sys("write_lock error");
        }

        TELL_CHILD(pid);

        if(waitpid(pid,NULL,0) < 0){
            err_sys("wait pid error");
        }
    }else{
        WAIT_PARENT();

        // 设置为非阻塞
        if((val = fcntl(fd, F_SETFD, O_NONBLOCK) <0)){
            err_sys("fcntl err");
        }
        if (read_lock(fd,0,SEEK_SET,0) !=-1){
            err_sys("child:read_lock ssucceeded");
        }

        printf("read_lock of alread-locked regioin returns %d\n", errno);

        if(lseek(fd, 0, SEEK_SET) == -1){
            err_sys("lseek error");
        }

        if(read(fd,buf,2) <0){
            err_sys("read failed ");
        }else{
            printf("read ok   buf = %2.2s\n", buf);
        }
    }

    exit(0);
}