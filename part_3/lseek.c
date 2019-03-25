#include "apue.h"
#include<fcntl.h>

char buf1[] = "12345678";
char buf2[] = "5340lwq";
// mac下空洞不会占用文件块
int main(void){
    int fd;
    if ((fd = creat("hello.txt", FILE_MODE)) <0 ){
        err_sys("create error");
    }

    if (write(fd, buf1, 10) != 10){
        err_sys("write error");
    }

    if (lseek(fd, 100, SEEK_SET) == -1){
        err_sys("seek error");
    }

    if (write(fd, buf2, 10) != 10){
        err_sys("write error");
    }
    exit(0);
}