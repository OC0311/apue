#include "apue.h"
#include <fcntl.h>
int
main (int argc, char *argv[]){
    int i,fd;

    struct stat statbuf;
    struct timespec times[2];
    for (i=1 ; i<argc ;i++){
        // 获取文件属性 返回值到buf 中
        if (stat(argv[i],&statbuf) < 0){
            err_ret(
                "%sstt error",argv[i]
            );
            continue;

        }

        if ((fd = open(argv[i],O_RDWR | O_TRUNC)) <0){
            err_ret("%s:open error",argv[i]);
            continue;
        }
        // mac os 没有timespec 结构
        times[0] = statbuf.st_atime;
        times[1] = statbuf.st_mtime;

        if (futimens(fd,times) < 0){
            err_ret("%s:futiens error",argv[i]);
            close(fd);
        }

    }
}