#include "apue.h"
#include <errno.h>
#include <fcntl.h>

char buf[500000];

int 
main (void){
    int ntowrite, nwrite;
    char *ptr;
    int val;
    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes \n", ntowrite);

    // 设置为非阻塞
    // set_fl(STDIN_FILENO, O_NONBLOCK);
    if((val = fcntl(STDIN_FILENO, F_SETFD, O_NONBLOCK) <0)){
        err_sys("fcntl err");
    }
    ptr = buf;
    while(nwrite > 0){
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

        if (nwrite > 0){
            ptr+=nwrite;
            ntowrite -= nwrite;

        }              
     }

    //  clr_fl(STDERR_FILENO, O_NONBLOCK);
    if((val = fcntl(STDOUT_FILENO, F_SETFD, O_NONBLOCK) <0)){
        err_sys("fcntl err");
    }
     exit(0);
}