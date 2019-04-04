#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
int main(void){
    umask(0);
    if(creat("foo", RWRWRW) <0){
        err_sys("create foo error :%s",RWRWRW);
    }

    // 屏蔽相关权限
    umask(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (creat("bar", RWRWRW) <0){
        err_sys("create  bar error:%s",RWRWRW);    
    }
    exit(0);
}
