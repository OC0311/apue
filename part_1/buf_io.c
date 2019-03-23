#include "apue.h"

#define BUFFSIZE 4096


// 执行 ./a.out < a.tx > b.tx
int main(void){
    int n;
    char buf[BUFFSIZE];
    // 不断读到buf 中
    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
        // 从buf从buf中写入
        if (write(STDOUT_FILENO, buf,n) !=n){
            err_sys("write error");
        }
    }
    if (n < 0){
        err_sys("read error");
    }
    exit(0);
}