#include"apue.h"
#include<stdlib.h>

void exit1(void){
    printf("call exit1..... \n");
}

void exit2(void){
    printf("call exit2..... \n");
}


int main(void){
    // 顺序相反  估计使用栈实现的
    // 可以被登记多次
    if (atexit(exit1) <0){
        err_sys("call exit1 error");
    }
    if (atexit(exit1) <0){
        err_sys("call exit1 error");
    }
    if ((atexit(exit2) <0)){
        err_sys("call exit2 error");
    }

    printf("main done");
    return 0;
}