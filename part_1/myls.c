#include"apue.h"
#include<dirent.h>

int 
main (int argc,char *argv[1]){
    DIR *dp;
    // 定义目录存储变量
    struct dirent *dirp;

    if (argc != 2)
        err_quit("输入目录名称");
    // 打开目录
    if ((dp = opendir(argv[1])) == NULL)
        err_sys("不能打开目录:%s",argv[1]);
    // 读取目录
    while((dirp = readdir(dp)) != NULL){
        printf("%s\n:",dirp->d_name);
    }
    
    closedir(dp);
    exit(0);
}