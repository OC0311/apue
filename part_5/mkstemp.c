#include "apue.h"
#include <errno.h>

void make_temp(char *template);

int main(){
    char good_template[] = "/tmp/dirXXXXXX";
    // 指针自身在栈上 该字符串只在只读栈中
    char *bad_template = "/tmp/dirXXXXXX";

    printf("trying to create first temp temp file ...\n");
    make_temp(good_template);

    printf("try to create second file ...\n");
    // 发生错误
    make_temp(bad_template);
    exit(0);
}

void make_temp(char *template){
    int fd;
    struct stat sbuf;
    if ((fd = mkstemp(template)) < 0){
        err_sys("can't crate temp file");
    }

    printf("temp name =%s\n", template);
    close(fd);

    if (stat(template,&sbuf) <0 ){
        if (errno == ENOENT){
            printf("file doesn't exist\n");
        }else{
            err_sys("stat failed");
        }
    }else{
        printf("file exists \n");
        // 需要手动删除
        // 注释掉后可以查找到该文件
        unlink(template);
    }
}