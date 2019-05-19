#include "apue.h"
#include <pthread.h>

int quitflag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;


// 相关概念：阻塞信号就是把信号接收到的信号变为未决，然后等解除阻塞的时候
// 才会执行对应的处理函数

void * thr_fn(void *arg){
    int err ,signo;
    for(;;){
        // 就是等到信号没有别的意识
        err = sigwait(&mask, &signo);
        if (err != 0){
            err_exit(err, "sigwait failed");
        }

        switch(signo){
        // ctrl+c
        case SIGINT:
            printf("\n interrupt! \n");
            break;
        // ctrl+\\
        case SIGQUIT:
            pthread_mutex_lock(&lock);
            quitflag = 1;
            printf("\n quit! \n");
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&waitloc);
            return 0;
        default:
            printf("unexpected signal %d\n", signo);
            exit(1);
        }

    }
}


int main(void){
    int err;
    sigset_t oldmask;
    pthread_t tid;

    // 设置屏蔽，将原先的信号全部变为0
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);

    // SIG_BLOCK：设置要阻塞的信号
    // &mask: 用于设置屏蔽信号集
    // &oldmask: 保存之前的信号集
    if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0){
        err_exit(err, "SIG_BLOCK error");
    }

    err = pthread_create(&tid, NULL, thr_fn, 0);
    if (err != 0){
        err_exit(err, "can't create thread");
    }

    pthread_mutex_lock(&lock);
    // 等到信号触发修改qui
    while(quitflag == 0){
        pthread_cond_wait(&waitloc, &lock);
    }
    pthread_mutex_unlock(&lock);

    quitflag = 0;

    // 使用oldmask设置
    // 重置信号将信号变为非阻塞
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        err_sys("SIG_SETMASK error");
    }

    exit(0);

}