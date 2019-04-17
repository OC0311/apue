#include "apue.h"
int iii = 1000;
int qqq = 1000;
int aaa = 1000;
int zzz = 1000;
int eee = 1000;
int ttt = 1000;
int bbb = 1000;
int ppp = 1000;
int main(int argc, char *argv[]){
    int i;
    // 第一个参数为程序名
    for(i = 0;i < argc; i++){
        printf("argv[%d]:%s\n",i ,argv[i]);
    }
    exit(0);
}