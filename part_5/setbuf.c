#include "apue.h"

int main(){
    // setbuf(stdout,NULL);
    int i;
    pid_t pid;

    if ((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid == 0){
        for (i = 0;i<10;i++){
            printf("test111");
            fflush(stdout);
        }
    }else{
         for (i = 0;i<10;i++){
            printf("test");
        }
    }

   
}