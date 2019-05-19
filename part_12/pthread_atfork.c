#include "apue.h"
#include <pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void){
    int err;
    printf("准备...lock\n");
    if((err = pthread_mutex_lock(&lock1)) != 0){
        err_cont(err,"can't lock lock1 in prepare handler");
    }

    if((err = pthread_mutex_lock(&lock2)) != 0){
        err_cont(err, "can't lock lock2 in prepare handler");
    }

}

void parent(void){
    int err;
    printf("父亲...unlock\n");
    if((err = pthread_mutex_unlock(&lock1)) != 0){
        err_cont(err,"can't lock lock1 in parent handler");
    }

    if((err = pthread_mutex_unlock(&lock2)) != 0){
        err_cont(err, "can't lock lock2 in parent handler");
    }
}

void child(void){
     int err;
    printf("儿子...unlock\n");
    if((err = pthread_mutex_unlock(&lock1)) != 0){
        err_cont(err,"can't lock lock1 in child handler");
    }

    if((err = pthread_mutex_unlock(&lock2)) != 0){
        err_cont(err, "can't lock lock2 in child handler");
    }
}

void *thr_fn(void *arg){
    printf("thread started...\n");
    pause();
    return (0);

}


// 主进程fork 出来的子进程也继承了主进程的锁
// 但是子进程并不知道主进程锁的状态，所以就是使用pthread_atfork 中的三个函数
// 进行清理工作
int main(void){
   int err;
   pid_t pid;
   pthread_t tid;

   if ((err = pthread_atfork(prepare, parent, child)) != 0){
       err_exit(err, "can't install fork handlers");

   }

   if((err = pthread_create(&tid, NULL, thr_fn,0)) != 0){
       err_exit(err, "can't create thread");
   }

   sleep(2);
   printf("parent about to fork ...\n");

   if ((pid = fork()) < 0){
       err_quit("fork failed");
   }else if(pid == 0){
       printf("child returned from fork\n");
   }else{
       printf("parent returned form fork\n");
   }

   exit(0);
}