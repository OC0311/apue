#include "apue.h"
#include<fcntl.h>

int main(){
    int fd;
    int val;
    if ((fd = open("./hello.txt",O_WRONLY)) < 0 ){
        err_sys("open error");
    }

    if ((val = fcntl(fd,F_GETFD)) < 0){
        err_sys("get status error");
    }

    printf("%d:",val);


}