#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char *s){
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s ,(unsigned long)pid,(unsigned long)tid,(unsigned long)tid);
}

void * thr_fn(void *arg){
   printids("new thread :");
   return ((void *) 0);
}

int main(void){
    int err;
    // create 参数说明
    // 1：线程id
    // 2：线程属性
    // 3：线程执行的函数
    // 4：函数的参数 如果是多个需要弄成一个结构体的指针传入
    err = pthread_create(&ntid, NULL, thr_fn, NULL);

    if (err != 0){
        err_exit(err, "cant create pthread!!!");
    }

    printids("main thread :");
    sleep(1);

    exit(0);
}