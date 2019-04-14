#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int main(){
    time_t t;
    struct tm *tmp;
    // 长度需要存的下处理结果
    char buf1[10];
    char buf2[64];

    time(&t);
    // 转换为本地时间
    tmp = localtime(&t);

    if (strftime(buf1,16,"time and date1 :%r,%a,%b,%d,%Y,%p",tmp) == 0){
        printf("buffer length 16 is too small1 \n");
    }else{
        printf("---%s\n",buf1);
    }

    if (strftime(buf2,64,"time and date2 :%r,%a,%b,%d,%Y，%U",tmp) == 0){
        printf("buffer length 64 is too small2 \n");
    }else{
        printf("%s\n",buf2);
    }
    
    exit(0);
}
