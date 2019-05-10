#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo){

    struct passwd *rootptr;
    printf("in signal handler \n");
    if ((rootptr = getpwnam("root")) == NULL){
        err_sys("getpwam(root) error");

    }
    alarm(1);

}

int main(void){
    struct passwd *ptr;
    // 注册信号处理函数
    signal(SIGALRM,my_alarm);
    for (;;){
        // 需要设置为自己用的户名
        // 更具提供的用户名 在/etc/master，查找相关的信息
        if((ptr = getpwnam("rjj")) == NULL){
            err_sys("getpwnam error");
        }
        if(strcmp(ptr->pw_name,"rjj") !=0 ){
            printf("return value corrupted ! pw_name=%s\n",ptr->pw_name);
        }
    }
}