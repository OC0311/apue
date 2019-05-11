#include "apue.h"
#include <pthread.h>

void * thr_fn1(void *arg){
    printf("thread 1 returning\n");
    // 直接返回也是可以直接退出线程的
    // 故意停一下一下
    sleep (5);
    return ((void *) 1);

}

void * thr_fn2(void *arg){
    printf("thread 2 exiting\n");
    pthread_exit((void *) 1);
}

// 使用pthread_join 函数来阻塞指定线程知道退出
// 并且可以该获取进程的退出状态
// pthread_exit 和 return 返回是一样的

int main(void){
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL,thr_fn1, NULL);
    if (err != 0){
        err_exit(err, "can't crate thread 1");
    }

    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0){
        err_exit(err, "can't crate thread 2");
    }
    // sleep (5)
    err = pthread_join(tid1, &tret);
    if (err != 0){
        err_exit(err, "can't join thread 1");
    }
    printf("thread 1 exit code %ld\n", (long)tret);
    err = pthread_join(tid2, &tret);
    if (err != 0){
        err_exit(err, "can't join thread 2");
    }

    printf("thread 2 exit code %ld\n", (long)tret);
    exit(0);
}