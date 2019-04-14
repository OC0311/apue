#include "apue.h"

int main(void){
    // 栈地址 至少有L_tmpnam的内存
    char name[L_tmpnam] ,line[MAXLINE];
    FILE *fp;

    printf("%s null：\n",tmpnam(NULL));
    tmpnam(name);

    printf("%s name：\n",name);
    // 根据tmpnam文件名生成文件
    // 退出会删除文件
    if ((fp = tmpfile() ) == NULL){
        err_sys("tmpfile error");
    }

    fputs("one lin eif output \n",fp);
    
    rewind(fp); // 指向头

    if (fgets(line, sizeof(line),fp) == NULL){
        err_sys("fgets errors");
    }

    fputs(line, stdout);
  
    exit(0);
}