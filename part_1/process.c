#include "apue.h"
int main(){
    // printf("pid:%ld\n",(long)getpid());
    // 使用长整形可以提高移植性
    printf("pid:%d\n", getpid());
}

