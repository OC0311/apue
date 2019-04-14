#include "apue.h"

int main(){
    // 不能使用指针，会导错误，字符常量不能被改变
    // char *str
    char str[30]; 
    if (gethostname(str,30) < 0){
        err_sys("get host name error");
    }
    printf("hostname:%s",str);
}