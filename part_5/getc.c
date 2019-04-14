#include"apue.h"


// 命令行是行缓冲：1024
// 文件是全缓冲 ：指定的大小
int 
main(){
    int c,count = 0;
    FILE *fp;
    fp = fopen("./a.tx", "ab+");
    printf("%d",fp->_flags);
    // 读取单个字符
     while((c = getc(fp)) != EOF){
       
         if (putc(c,fp) == EOF){
            err_sys("output error");
         }

         if (ferror(fp)){
             err_sys(
                "input error"
             );
         }

     }

     fflush(fp);

     exit(0);
}