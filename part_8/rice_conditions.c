#include "apue.h"

static void charatatime(char *);

int main(void) {
    pid_t pid;
    TELL_WAIT();

    if ((pid = fork() <0)){
        err_sys("fork error");
    }else if(pid == 0){
        WAIT_PARENT();
        charatatime("output from chaild \n");
    }else{
        charatatime("Output from parent \n");
        TELL_CHILD(pid);
    }
    exit(0);
}


static void charatatime(char *str){
    char *ptr;
    int c;
    // 设置不缓冲所以每次都都会进行系统调用，导致进程切换
    setbuf(stdout, NULL);
    for (ptr = str; (c = *ptr++) != 0;){
        putc(c, stdout);
    }


}