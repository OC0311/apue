#include "apue.h"
#include <pthread.h>

// 静态初始化
// mux_lock用于条件保护变量
pthread_mutex_t mux_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond_lock = PTHREAD_COND_INITIALIZER;
int cond;

void *pthread_1(void *arg){

    for (;;)
    {
         pthread_mutex_lock(&mux_lock);
         while (cond == 1)
         {
            pthread_cond_wait(&cond_lock, &mux_lock);
         }
        printf("进来了：%d\n", cond);
        cond --;
        pthread_mutex_unlock(&mux_lock);
    }
    pthread_exit((void *)0);
}

void *pthread_2(void *arg){
    for(;;){
        sleep(1);
        pthread_mutex_lock(&mux_lock);
        cond = 0;
        pthread_mutex_unlock(&mux_lock);
        pthread_cond_signal(&cond_lock);
    }
    pthread_exit((void *)0); 
}

void *pthread_3(void *arg){
    for(;;){
        sleep(3);
        pthread_mutex_lock(&mux_lock);
        cond = 1;
        pthread_mutex_unlock(&mux_lock);
        pthread_cond_signal(&cond_lock);
    }
   
    pthread_exit((void *)0); 
}

int main(void){
    int err;
    pthread_t pid1,pid2,pid3;
    cond = 0;

   err = pthread_create(&pid1, NULL,pthread_1,NULL);
   if (err != 0){
        err_exit(err ,"create pthread_1 err:%d");
   }

   err = pthread_create(&pid2, NULL, pthread_2, NULL);
   if (err != 0){
       err_exit(err, "create pthread_1 err:%d");
   }

    err = pthread_create(&pid3, NULL, pthread_3, NULL);
   if (err != 0){
       err_exit(err, "create pthread_1 err:%d");
   }

   err = pthread_join(pid1, NULL);
   if (err != 0){
       err_exit(err, "join pthread_1 err:%d");
   }

   err = pthread_join(pid2, NULL);
   if (err != 0){
       err_exit(err, "join pthread_2 err:%d");
   }

   err = pthread_join(pid3, NULL);
   if (err != 0){
       err_exit(err, "join pthread_2 err:%d");
   }

    return 0;
}

