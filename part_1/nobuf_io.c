#include "apue.h"

int 
main(void){
    int c;
    // 每次读取一个字节
    while((c = getc(stdin)) != EOF){
        if (putc(c,stdout) == EOF){
            err_sys("output error");
        }
    }
    if (ferror(stdin)){
        err_sys("intput error");
    }
    exit(0);
}