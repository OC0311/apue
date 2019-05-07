#include "apue.h"
// #include <sys/signal.h>
static void sig_usr(int);
int main(void){
    if (signal(SIGUSR1,sig_usr) == SIG_ERR){
        err_sys("can't catch sigerr1");
    }

    if (signal(SIGUSR2,sig_usr) == SIG_ERR){
        err_sys("can't catch sigerr2");
    }

    for(;;){
        // 让信号暂停直到有信号进来为止
        pause();
    }
}

static void sig_usr(int signo){
    if( signo == SIGUSR1){
        printf("received SIGUSR1\n");
    }else if (signo == SIGUSR2) {
        printf("received SIGUSR2\n");
    }else{
        err_dump("received singal %d\n", signo);
    }
    
    
}