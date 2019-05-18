#include "apue.h"
#include<pthread.h>

// 初始化锁
pthread_mutex_t testlock = PTHREAD_MUTEX_INITIALIZER;

int main(void){

    // 同时加锁两次会导致死锁
    pthread_mutex_lock(&testlock);
    // 此处可以改为trylock
    // pthread_mutex_trylock(&testlock);
    pthread_mutex_lock(&testlock);
    // TODO
    pthread_mutex_unlock(&testlock);
 
    return 0;
}