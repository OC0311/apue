#include "apue.h"
#include <pthread.h>

void *
thread1(void *arg){
    // 为什么不是先执行打印在睡眠????
    // 因为标准输出是行缓冲，如果不加\n 会在退出时清空缓冲区
    printf("running thread one\n");
    sleep(3);
    pthread_exit((void *)1);
}

int 
main(void) {
    int err;
    pthread_t tid1;
    void *tret;

    err = pthread_create(&tid1, NULL, thread1, NULL);
    if (err != 0){
        err_exit( err,"create thread1 err");
    }
    // 对线程进行了分离
    // 所以下面的join 就会出错
    // pthread_detach(tid1);

    err = pthread_join(tid1, &tret);
    if (err != 0){
        err_exit(err, "join thread1 err");
    }

    exit(0);
}