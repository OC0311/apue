#include "apue.h"
#include <pthread.h>


void clean_up(void *arg){
    printf("清理线程：%s\n", (char *)arg);
}

void *
thread1(void *arg){
    // pthread_cleanup_push 和 pthread_cleanup_pop 是由宏实现所以必须同时出现
    // 否则会出现语法错误

    // 第二波会先执行
    pthread_cleanup_push(clean_up,"清理第一波");
    pthread_cleanup_push(clean_up,"清理第二波");

    if (arg){
        return ((void *)1);
    }
    // 参数为非0是会执行清理函数并且移除函数非0数都一样
    // 参数为0是只是移除  
    pthread_cleanup_pop(2);
    pthread_cleanup_pop(1);
    // 只有使用pthread_exit 才会调用clean_up 程序
    pthread_exit((void *)1);

    // return ((void *)1);
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


    // 对线程进行cancel 和使用ptread_exit()是一类似的只不过参数不同
    // pthread_cancel(tid1);

    err = pthread_join(tid1, &tret);
    if (err != 0){
        err_exit(err, "join thread1 err");
    }

    exit(0);
}