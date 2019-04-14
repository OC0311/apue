#include "apue.h"

#define BSZ 48

int main(){
    FILE *fp;
    char buf[BSZ];

    memset(buf,'a',BSZ-2);

    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';

    if ((fp = fmemopen(buf,BSZ,"w+")) ==NULL){
        err_sys("fmemopen failed");
    }

    printf("initial buffer contentsv :%s\n",buf);
    fprintf(fp,"hello, world");
    printf("before flush:%s\n",buf);
    // 写入一个null 字符
    fflush(fp);
    printf("after fflush :%s\n",buf);
    printf("len of stringin in buf =%ld\n",(long)strlen(buf));

    memset(buf,'b',BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp,"hello, world");
    // 写入一个null 字符
    fseek(fp,0,SEEK_SET);
    printf("after seek :%s\n",buf);
    printf("len of stringin in buf =%ld\n",(long)strlen(buf));


    memset(buf,'c',BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp,"hello, world");
    // 写入一个null 字符
    fclose(fp);
    printf("after close :%s\n",buf);
    printf("len of stringin in buf =%ld\n",(long)strlen(buf));

    return 0;

}